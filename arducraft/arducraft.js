//----------------------------------------------------------------------------//
/*
 *  Copyright (C) 2021  Filo Connesso - filoconnesso.it
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
 //----------------------------------------------------------------------------//

/*
 * FILO CONNESSO MINECRAFT LIBRARY
 *
 *
 * Created by Alessandro Marcon (@alessandromrc) and Mirko Pacioni
 * November 2th 2021
 *
 */

const mineflayer = require("mineflayer");
const serialPort = require("serialport");
const Readline = require("@serialport/parser-readline");
const inquirer = require("inquirer");
const { restoreDefaultPrompts } = require("inquirer");
const Vec3 = require("vec3").Vec3;

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
console.log("#          v. 1.0.0 beta1           #");
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
        return "63091";
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
      default() {
        return "ArduCraft";
      },
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

      const device = new serialPort(answers.serial_port, {
        baudRate: 115200,
      });

      const parser = device.pipe(new Readline({ delimiter: "\n" }));

      let moving = false;
      let MinecraftGameInformation;

      function botStop() {
        if (botStarted) {
          bot.setControlState("forward", false);
          bot.setControlState("back", false);
          bot.setControlState("left", false);
          bot.setControlState("right", false);
          bot.setControlState("jump", false);
          bot.lookAt(bot.entity.position.offset(0, bot.entity.height, 0));
          moving = false;
        }
      }

      let maxRefZ;
      let maxRefX;
      let minRefZ;
      let minRefX;
      let maxRefY;
      let minRefY;

      const ReadSerialPort = async () => {
        parser.on("data", (data) => {
          if (botStarted) {
            let command = data;
            command = command.replace(/(\r\n|\n|\r)/gm, "");
            if (command.indexOf("[ARDUINO CMD] bot walk forward") > -1) {
              maxRefZ = Math.floor(bot.entity.position.z) + 1.0;
              maxRefX = Math.floor(bot.entity.position.x) + 1.0;
              minRefZ = Math.floor(bot.entity.position.z);
              minRefX = Math.floor(bot.entity.position.x);
              bot.setControlState("forward", true);
              moving = true;
            } else if (command.indexOf("[ARDUINO CMD] bot walk back") > -1) {
              maxRefZ = Math.floor(bot.entity.position.z) + 1.0;
              maxRefX = Math.floor(bot.entity.position.x) + 1.0;
              minRefZ = Math.floor(bot.entity.position.z);
              minRefX = Math.floor(bot.entity.position.x);
              bot.setControlState("back", true);
              moving = true;
            } else if (command.indexOf("[ARDUINO CMD] bot walk left") > -1) {
              maxRefZ = Math.floor(bot.entity.position.z) + 1.0;
              maxRefX = Math.floor(bot.entity.position.x) + 1.0;
              minRefZ = Math.floor(bot.entity.position.z);
              minRefX = Math.floor(bot.entity.position.x);
              bot.setControlState("left", true);
              moving = true;
            }
            if (command.indexOf("[ARDUINO CMD] bot walk right") > -1) {
              maxRefZ = Math.floor(bot.entity.position.z) + 1.0;
              maxRefX = Math.floor(bot.entity.position.x) + 1.0;
              minRefZ = Math.floor(bot.entity.position.z);
              minRefX = Math.floor(bot.entity.position.x);
              bot.setControlState("right", true);
              moving = true;
            }
            if (command.indexOf("[ARDUINO CMD] bot jump") > -1) {
              maxRefY = Math.floor(bot.entity.position.y) + 1.0;
              minRefY = Math.floor(bot.entity.position.y);
              bot.setControlState("jump", true);
              moving = true;
            }
            if (command.indexOf("[ARDUINO CMD] bot walk stop") > -1) {
              botStop();
            } else if (command.indexOf("[ARDUINO CMD] bot placeblock") > -1) {
              let currentBlock = command.replace("[ARDUINO CMD] bot placeblock","");
              currentBlock = currentBlock.trim(currentBlock);
              bot.chat("/fill ~ ~ ~ ~ ~ ~ " + currentBlock);
            } else {
              if (!moving) {
                command = command.trim(command);
                console.log(`BOT CONSOLE >>> ${command}`);
                bot.chat(command);
              }
            }
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
          ping: 0,
          x: 0,
          y: 0,
          z: 0,
          botMoving: false,
          lastMessage: null
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

      bot.on("move", function () {
        if (moving) {
          if (
            bot.entity.position.x >= maxRefX ||
            bot.entity.position.x <= minRefX
          ) {
            botStop();
            return;
          }
          if (
            bot.entity.position.z >= maxRefZ ||
            bot.entity.position.z <= minRefZ
          ) {
            botStop();
            return;
          }
          if (bot.entity.position.y > maxRefY) {
            botStop();
            return;
          }
        }
      });

      bot.on("spawn", function () {
        console.log("BOT CONSOLE >>> The bot appeared on the map");
        minecraft_datas[0]["spawn"] = true;
        botStarted = true;
        MinecraftGameInformation = require("minecraft-data")(bot.version);
        bot.lookAt(bot.entity.position.offset(0, bot.entity.height, 0));
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
          let axis = bot.entity.position;
          minecraft_datas[0]["worldTime"] = bot.time.timeOfDay;
          minecraft_datas[0]["botExperience"] = bot.experience.points;
          minecraft_datas[0]["botHealth"] = bot.health;
          minecraft_datas[0]["botFood"] = bot.food;
          minecraft_datas[0]["botOxygen"] = bot.oxygenLevel;
          minecraft_datas[0]["botGameMode"] = bot.game.gameMode;
          minecraft_datas[0]["raining"] = bot.isRaining;
          minecraft_datas[0]["ping"] = bot.player.ping;
          minecraft_datas[0]["x"] = axis.x;
          minecraft_datas[0]["y"] = axis.y;
          minecraft_datas[0]["z"] = axis.x;
          minecraft_datas[0]["botMoving"] = moving;
          let minecraft_datas_string = "";
          minecraft_datas.forEach((datas) => {
            Object.entries(datas).forEach(([dataType, dataValue]) => {
              minecraft_datas_string += `${dataValue};`;
            });
          });
          minecraft_datas_string += "endata";
          device.write(minecraft_datas_string + "\n");
          if (minecraft_datas[0]["kicked"] || minecraft_datas[0]["error"]) {
            botStarted = false;
          }
          restoreBotDataLifeStatus();
        }
      }
      
      setInterval(sendMinecraftData, 100);

      bot.on("chat", (username, message) => {
        if (botStarted) {
          if (username === bot.username) return;
          minecraft_datas[0]["lastMessage"] = message;
        }
      });


    });
}
