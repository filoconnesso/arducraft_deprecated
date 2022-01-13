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
const Rx = require("rxjs");
const fs = require("fs");

let data = {};
let isArduinoReady = false;
let ProcessArguments = process.argv.slice(2);

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

function getSerialSerialPorts() {
  return new Promise((resolve) => {
    let Ports = [];
    serialPort.list().then((ports) => {
      ports.forEach((port) => {
        Ports.push(port.path);
      });
      resolve(Ports);
    });
  });
}

//arguments start example: node arducraft.js /dev/cu.usbmodem13301 192.168.178.74 56893 1.17.1 ArduCraft
async function Init(Arguments) {
  //check if config.json exists and load the bot without asking for arguments
  const Portlist = await getSerialSerialPorts();

  //configuration data
  let configData = {
    serial_port: "",
    hostname: "",
    port: "",
    version: "",
    bot_name: "",
  };

  if(fs.existsSync("./config.json") && Arguments[0] == "--clean") {
    fs.unlinkSync("./config.json");
  }

  if (fs.existsSync("./config.json") && Arguments.length == 0) {
    console.log("Loading config.json...");
    data = JSON.parse(fs.readFileSync("./config.json"));
    console.log("Config.json loaded!");
    console.log("Starting bot...");
    StartBot(
      data.serial_port,
      data.hostname,
      data.port,
      data.version,
      data.bot_name
    );
  }

  if (Arguments.length >= 4) {

    configData.serial_port = Arguments[0];
    configData.hostname = Arguments[1];
    configData.port = Arguments[2];
    configData.version = Arguments[3];
    configData.bot_name = Arguments[4];

    //save config data to file
    let data = JSON.stringify(configData);
    console.log("Creating config.json...");
    fs.writeFileSync("config.json", data);
    console.log("Config.json created!");
    console.log("Starting bot...");
    StartBot(
      arguments[0][0],
      arguments[0][1],
      arguments[0][2],
      arguments[0][3],
      arguments[0][4]
    );
    
  } else if (!fs.existsSync("./config.json")) {
    inquirer
      .prompt([
        {
          name: "serial_port",
          type: "rawlist",
          message: "Indicate the serial port:",
          choices: Portlist,
        },
        {
          name: "hostname",
          type: "input",
          message: "Indicate the hostname: ",
          default: "localhost",
        },
        {
          name: "port",
          type: "input",
          message: "Indicate the port: ",
          default: "25565",
        },
        {
          name: "version",
          type: "input",
          message: "Indicate the server version: ",
          default: "1.17.1",
        },
        {
          name: "bot_name",
          type: "input",
          message: "Indicate the bot name: ",
          default: "ArduCraft",
        },
      ])
      .then((answers) => {
        //save config data to file
        let data = JSON.stringify(answers);
        console.log("Creating config.json...");
        fs.writeFileSync("config.json", data);
        console.log("Config.json created!");
        console.log("Starting bot...");
        StartBot(
          answers.serial_port,
          answers.hostname,
          answers.port,
          answers.version,
          answers.bot_name
        );
      });
  }

  function StartBot(serial_port, hostname, port, version, bot_name) {
    const bot = mineflayer.createBot({
      host: hostname,
      port: parseInt(port),
      username: bot_name,
      version: version,
    });
    const device = new serialPort(serial_port, {
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
            maxRefZ = Math.floor(bot.entity.position.z) + 1.2;
            maxRefX = Math.floor(bot.entity.position.x) + 1.2;
            minRefZ = Math.floor(bot.entity.position.z);
            minRefX = Math.floor(bot.entity.position.x);
            bot.setControlState("forward", true);
            moving = true;
          } else if (command.indexOf("[ARDUINO CMD] bot walk back") > -1) {
            maxRefZ = Math.floor(bot.entity.position.z) + 1.2;
            maxRefX = Math.floor(bot.entity.position.x) + 1.2;
            minRefZ = Math.floor(bot.entity.position.z);
            minRefX = Math.floor(bot.entity.position.x);
            bot.setControlState("back", true);
            moving = true;
          } else if (command.indexOf("[ARDUINO CMD] bot walk left") > -1) {
            maxRefZ = Math.floor(bot.entity.position.z) + 1.2;
            maxRefX = Math.floor(bot.entity.position.x) + 1.2;
            minRefZ = Math.floor(bot.entity.position.z);
            minRefX = Math.floor(bot.entity.position.x);
            bot.setControlState("left", true);
            moving = true;
          }
          if (command.indexOf("[ARDUINO CMD] bot walk right") > -1) {
            maxRefZ = Math.floor(bot.entity.position.z) + 1.2;
            maxRefX = Math.floor(bot.entity.position.x) + 1.2;
            minRefZ = Math.floor(bot.entity.position.z);
            minRefX = Math.floor(bot.entity.position.x);
            bot.setControlState("right", true);
            moving = true;
          }
          if (command.indexOf("[ARDUINO CMD] bot jump") > -1) {
            maxRefY = Math.floor(bot.entity.position.y) + 1.2;
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
          } else if(command.indexOf("[ARDUINO CMD] chatlink=") > -1) {
            let currentChatLink = command.replace("[ARDUINO CMD] chatlink=","");
            let linkParams = currentChatLink.split('+');
            bot.chat(`/tellraw @a {\"text\":\"${linkParams[0]}\",\"color\":\"${linkParams[1]}\",\"bold\":\"true\",\"underlined\":\"true",\"clickEvent\":{\"action\":\"open_url\",\"value\":\"${linkParams[2]}\"}}`);
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
        lastMessage: null,
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
      bot.chat("Welcome to ArduCraft, for updates check us on Github at Filo Connesso!");
      bot.chat("/tellraw @a {\"text\":\">>> Click for Github Repository <<<\",\"color\":\"red\",\"bold\":\"true\",\"underlined\":\"true\",\"clickEvent\":{\"action\":\"open_url\",\"value\":\"https://github.com/filoconnesso/arducraft\"}}");
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
  }
}

Init(ProcessArguments);
