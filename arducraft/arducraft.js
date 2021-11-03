const mineflayer = require("mineflayer");
const serialPort = require("serialport");
const Readline = require("@serialport/parser-readline");
const inquirer = require("inquirer");
const { restoreDefaultPrompts } = require("inquirer");

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
      default() {
        return "localhost";
      },
    },
    {
      type: "input",
      name: "port",
      message: "Indicate the port: ",
      default() {
        return "61989";
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
          if (botStarted) {
            let command = data;
            command = command.replace(/(\r\n|\n|\r)/gm, "");
            console.log(`BOT CONSOLE >>> ${command}`);
            bot.chat(command);
          }
        });
      };

      ReadSerialPort();

      let botStarted = false;
      let minecraft_datas = [];

      minecraft_datas = [
        {
          spawn: false,
          kicked: false,
          end: false,
          death: false,
          health: false,
          error: false,
          errorMessage: null,
          worldTime: 0,
          botExperience: 0,
          botHealth: 0,
          botFood: 0,
          botOxygen: 0,
          botGameMode: null,
          raining: false,
        },
      ];

      async function restoreBotDataLifeStatus() {
        minecraft_datas.forEach((datas) => {
          Object.entries(datas).forEach(([dataType, dataValue]) => {
            if (
              dataType == "spawn" ||
              dataType == "kicked" ||
              dataType == "end" ||
              dataType == "death" ||
              dataType == "health" ||
              dataType == "error"
            ) {
              minecraft_datas[0][dataType] = false;
            }
          });
        });
      }

      bot.on("spawn", function () {
        console.log("BOT CONSOLE >>> The bot appeared on the map");
        minecraft_datas[0]["spawn"] = true;
        botStarted = true;
      });
      bot.on("kicked", function () {
        console.log("BOT CONSOLE >>> The bot got kicked");
        minecraft_datas[0]["kicked"] = true;
      });
      bot.on("end", function () {
        console.log("BOT CONSOLE >>> The bot is out");
        minecraft_datas[0]["end"] = true;
      });
      bot.on("death", function () {
        console.log("BOT CONSOLE >>> The bot is dead");
        minecraft_datas[0]["death"] = true;
      });
      bot.on("health", function () {
        console.log("BOT CONSOLE >>> The bot's health has changed");
        minecraft_datas[0]["health"] = true;
      });
      bot.on("error", function (error_message) {
        console.log(`BOT CONSOLE >>> The bot gave an error : ${error_message}`);
        minecraft_datas[0]["errorMessage"] = error_message;
        minecraft_datas[0]["error"] = true;
      });

      function sendMinecraftData() {
        if (botStarted) {
          minecraft_datas[0]["worldTime"] = bot.time.timeOfDay;
          minecraft_datas[0]["botExperience"] = bot.experience.points;
          minecraft_datas[0]["botHealth"] = bot.health;
          minecraft_datas[0]["botFood"] = bot.food;
          minecraft_datas[0]["botOxygen"] = bot.oxygenLevel;
          minecraft_datas[0]["botGameMode"] = bot.game.gameMode;
          minecraft_datas[0]["raining"] = bot.isRaining;
          let minecraft_datas_string = "[DEAMON-CMD] datas ";
          minecraft_datas.forEach((datas) => {
            Object.entries(datas).forEach(([dataType, dataValue]) => {
              minecraft_datas_string += `${dataValue};`;
            });
          });
          minecraft_datas_string += "endata";
          device.write(minecraft_datas_string + "\n");
          if(minecraft_datas[0]["kicked"] || minecraft_datas[0]["error"]) {
            botStarted = false;
          }
          restoreBotDataLifeStatus();
        }
      }

      setInterval(sendMinecraftData, 10);

      bot.on("chat", (username, message) => {
        if(botStarted) {
          if (username === bot.username) return;
          console.log(`BOT CONSOLE >>> ${username} : ${message}`);
          device.write(message + "\n");
        }
      });

      bot.on("physicTick", lookAtPlayer);
    });
}
