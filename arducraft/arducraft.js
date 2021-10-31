const mineflayer = require("mineflayer");
const serialPort = require("serialport");
const Readline = require("@serialport/parser-readline");

const inquirer = require("inquirer");

let data = {};
const delay = (ms) => new Promise((res) => setTimeout(res, ms));

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

function DaemonCommandParser(message) {
  return message.includes("[DAEMON-CMD]");
}

function Main() {
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
        await delay(2000);
        parser.on("data", (data) => {
          let command = data;
          command = command.replace(/(\r\n|\n|\r)/gm, "");
          console.log(command);
          if (DaemonCommandParser(command)) {
            command = command.replace("[DAEMON-CMD] ", "");
            switch (command) {
              case "getTime":
                device.write("[TIME-RESPONSE] " + bot.time.timeOfDay);
                break;
            }
          } else {
            console.log(command);
            bot.chat(command);
          }
        });
      };

      ReadSerialPort();

      bot.on("chat", (username, message) => {
        if (username === bot.username) return;
        device.write(message + "\n");
      });

      bot.on("physicTick", lookAtPlayer);
      bot.on("kicked", console.log);
      bot.on("error", console.log);
    });
}
