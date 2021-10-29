const mineflayer = require("mineflayer");
const serialPort = require("serialport");
const read = require("readline").createInterface({
  input: process.stdin,
  output: process.stdout,
});

read.question("Indicate the port : \n", (new_com) => {
  if (new_com != "") {
    console.log("Arducraft Daemon is running...");
    device = new serialPort(new_com, { baudRate: 115200 });
    MainBot();
  }
});

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

function MainBot() {
  const bot = mineflayer.createBot({
    host: "fcadventures.mcpro.io", // minecraft server ip
    port: 25565, // only set if you need a port that isn't 25565
    // version: false,             // only set if you need a specific version or snapshot (ie: "1.8.9" or "1.16.5"), otherwise it's set automatically
    // auth: 'mojang'              // only set if you need microsoft auth, then set this to 'microsoft'
    username: "FiloIndianoBot",
  });

  bot.on("chat", (username, message) => {
    if (username === bot.username) return;
    bot.chat("/time set day");
    console.log(`${username} said "${message}"`);
    device.write(message + "\n");
  });

  function lookAtPlayer() {
    const playerFilter = (entity) => entity.type === "player";
    const playerEntity = bot.nearestEntity(playerFilter);

    if (!playerEntity) return;

    const pos = playerEntity.position;
    bot.lookAt(pos);
  }

  bot.on("physicTick", lookAtPlayer);

  // Log errors and kick reasons:
  bot.on("kicked", console.log);
  bot.on("error", console.log);
}
