const os = require("os");
const fs = require("fs");
const readline = require("readline");
const stream = require("stream");
const serialPort = require("serialport");
const read = require("readline").createInterface({
  input: process.stdin,
  output: process.stdout,
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

var fileName = "";

if (os.platform == "win32") {
  fileName = process.env.APPDATA + "\\.minecraft\\logs\\latest.log";
} else if (os.platform == "darwin") {
  fileName = "";
} else if (os.platform == "linux") {
  fileName = "";
}

fs.access(fileName, fs.F_OK, (nofile) => {
  if (nofile) {
    console.log("Check that Minecraft is installed correctly!");
    while (1);
  }
});

serialPort.list().then(
  (ports) =>
    ports.forEach((port) =>
      console.log(port.path + " " + port.manufacturer + "\n")
    ),
  (err) => console.log(err)
);

var device;

read.question("Indicate the port : \n", (new_com) => {
  if (new_com != "") {
    console.log("Arducraft Daemon is running...")
    device = new serialPort(new_com, { baudRate: 115200 });
    setInterval(getLastLine, 10);
    read.close();
  }
});

function getLastLine() {

  var instream = fs.createReadStream(fileName);
  var outstream = new stream();
  var rl = readline.createInterface(instream, outstream);

  var currentLine;

  rl.on("line", function (line) {
    currentLine = line;
  });

  instream.on("end", function () {
      //console.log(currentLine);
      device.write(currentLine + "\n");
  });

}