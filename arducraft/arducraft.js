const mineflayer = require("mineflayer");
const serialPort = require("serialport");
const Readline = require("@serialport/parser-readline");
const inquirer = require("inquirer");

let data = {};
let isArduinoReady = false;

console.log("#####################################");
console.log("#                                   #");
console.log("#             ██████████            #");
console.log("#             █░░░░░░░░█            #");
console.log("#             █░██░░██░█            #");
console.log("#             █░░░░░░░░█            #");
console.log("#             █░░█░░█░░█            #");
console.log("#             █░░████░░█            #");
console.log("#             █░░░██░░░█            #");
console.log("#             ██████████            #");
console.log("#                                   #");
console.log("#  FILO CONNESSO ARDUCRAFT Daemon   #");
console.log("#             v. 0.0.1              #");
console.log("#                                   #");
console.log("#####################################");

let questions;

serialPort.list().then((ports) => {
  let Portlist = [];

  ports.forEach((port) => {
    Portlist.push(`${port.path}`);
  });

  questions = [
    {
      type: "rawlist",
      name: "serial_port",
      message: "Indicate the serial port: ",
      choices: Portlist,
    },
    {
      type: "input",
      name: "hostname",
      message: "Indicate the hostname: ",
    },
    {
      type: "input",
      name: "port",
      message: "Indicate the port: ",
      default() {
        return "25565";
      },
    },
    {
      type: "input",
      name: "version",
      message: "Indicate the server version: ",
      default() {
        return "1.17.1";
      },
    },
    {
      type: "input",
      name: "bot_name",
      message: "Indicate the bot name: ",
    },
  ];

  Main();
});

async function Main() {
  inquirer
    .prompt(questions)

    .then((answers) => {
      const bot = mineflayer.createBot({
        host: answers.hostname,
        port: parseInt(answers.port),
        username: answers.bot_name,
        version: answers.version,
      });

      function lookAtPlayer() {
        const playerFilter = (entity) => entity.type === "player";
        const playerEntity = bot.nearestEntity(playerFilter);
        if (!playerEntity) return;
        const pos = playerEntity.position;
        bot.lookAt(pos);
      }

      const device = new serialPort(answers.serial_port, {
        baudRate: 115200,
      });

      const parser = device.pipe(new Readline({ delimiter: "\n" }));

      const ReadSerialPort = async () => {
        parser.on("data", (data) => {
          if (data.includes("[ARDUINO-CMD] connect")) {
            device.write("[DEAMON-CMD] connected");
            isArduinoReady = true;
          }
          if (isArduinoReady) {
            let command = data;
            command = command.replace(/(\r\n|\n|\r)/gm, "");
            console.log(command);
            if (!data.includes("[ARDUINO-CMD] connect")) {
              console.log(command);
              bot.chat(command);
            }
          }
        });
      };

      ReadSerialPort();

      bot.on("chat", (username, message) => {
        if (username === bot.username) return;
        device.write(message + "\n");
      });

      bot.on("physicTick", lookAtPlayer);
    
      let current_bot_status = [];
      let current_bot_error_status = null;
      
      current_bot_status  = [
        {
          "spawn" : false,
          "kicked" : false,
          "end" : false,
          "death" : false,
          "health" : false,
          "error" : false
        }
      ];

      async function restoreStatus() {
        current_bot_status.forEach((element) => {
          Object.entries(element).forEach(([status, value]) => {
              if(status != "spawn") {
                current_bot_status[0]["status"] = false;
              }
          });
        });
      }

      bot.on("spawn", function () {
        restoreStatus();
        console.log("BOT CONSOLE >> The bot appeared on the map");
        current_bot_status[0]["spawn"] = true; 
      });
      bot.on("kicked", function () {
        restoreStatus();
        console.log("BOT CONSOLE >> The bot got kicked");
        current_bot_status[0]["kicked"] = true;
        current_bot_status[0]["spawn"] = false;
      });
      bot.on("end", function () {
        restoreStatus();
        console.log("BOT CONSOLE >> The bot is out");
        current_bot_status[0]["end"] = true; 
        current_bot_status[0]["spawn"] = false; 
      });
      bot.on("death", function () {
        restoreStatus();
        console.log("BOT CONSOLE >> The bot is dead");
        current_bot_status[0]["death"] = true;
        current_bot_status[0]["spawn"] = false;  
      });
      bot.on("health", function () {
        restoreStatus();
        console.log("BOT CONSOLE >> The bot's health has changed");
        current_bot_status[0]["health"] = true; 
      });
      bot.on("error", function (data_error) {
        restoreStatus();
        console.log("BOT CONSOLE >> The bot returned an error : " + data_error);
        current_bot_status[0]["error"] = true; 
        current_bot_status[0]["spawn"] = false; 
        current_bot_error_status = data_error;
      });

      async function sendStatus() {
        let status_string = "";
        current_bot_status.forEach((element) => {
          Object.entries(element).forEach(([status, value]) => {
              status_string += value + ",";
          });
        });
        status_string += current_bot_error_status;
        console.log("[DEAMON-CMD] botstatus " + status_string)
      }

      setInterval(sendStatus, 1000);

      async function sendTime() {
        device.write("[DEAMON-CMD] worldtime " + bot.time.timeOfDay);
      }

      setInterval(sendTime, 1000);
    });
}
