const mineflayer = require("mineflayer");
const serialPort = require("serialport");
const inquirer = require("inquirer");

let data = {};

const questions = [
  {
    type: "input",
    name: "serial_port",
    message: "Indicate the serial port: ",
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
  },
  {
    type: "input",
    name: "bot_name",
    message: "Indicate the bot name: ",
  },
];

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

serialPort.list().then(
  (ports) =>
    ports.forEach((port) =>
      console.log(port.path + " " + port.manufacturer + "\n")
    ),
  (err) => console.log(err)
);

function Main() {
  inquirer
    .prompt(questions)

    .then((answers) => {
      const bot = mineflayer.createBot({
        host: answers.hostname,
        port: parseInt(answers.port),
        username: answers.bot_name,
      });

      const device = new serialPort(answers.serial_port, { baudRate: 115200 });

      bot.on("chat", (username, message) => {
        if (username === bot.username) return;
        device.write(message + "\n");
      });

      device.on('open',function(){
        device.on('data', function(data){
          let datastring = data.toString();
          if(datastring.indexOf("botmessage:") != -1) {
             datastring = datastring.replace("botmessage:", "");
             console.log(datastring);
             bot.chat(datastring);
          }
        });
      });
    
      function lookAtPlayer() {
        const playerFilter = (entity) => entity.type === "player";
        const playerEntity = bot.nearestEntity(playerFilter);
    
        if (!playerEntity) return;
    
        const pos = playerEntity.position;
        bot.lookAt(pos);
      }
    
      bot.on("physicTick", lookAtPlayer);
      fcadventures.mcpro.io
      // Log errors and kick reasons:
      bot.on("kicked", console.log);
      bot.on("error", console.log);

  });
}

Main();