const connectbtn = document.getElementById('connect');
const disconnectbtn = document.getElementById('disconnectbtn');
const connectedwindow = document.getElementById('connectedwindow');
const portlistwindow = document.getElementById('portlistwindow');
const portlist = document.getElementById('portlist');
const comunicationport = document.getElementById('comport');
const serveraddress = document.getElementById('serveraddress');
const serverport = document.getElementById('serverport');
const serverversion = document.getElementById('serverversion');
const botname = document.getElementById('botname');
const connectionmsg = document.getElementById('connectionmsg');

let reflist = document.querySelector('#portlist');
let portselector = '.port-select';

const IPC_CHANNEL = 'ipc';

function updateComunicationPortList() {
    electron.ipcRenderer.send(IPC_CHANNEL, "UPDATE_SERIAL_PORT_LIST");
}

function toConnect(data) {
    electron.ipcRenderer.send(IPC_CHANNEL, "CONNECT" + "," + data);
}

function toDisconnect() {
    electron.ipcRenderer.send(IPC_CHANNEL, "DISCONNECT,NULL");
}

reflist.addEventListener('click', function (thisselector) {
  let closest = thisselector.target.closest(portselector);
  if (closest && reflist.contains(closest)) {
    portlistwindow.style.display = "none";
    comunicationport.value = thisselector.target.value;
  }
});

comunicationport.addEventListener('click', () => {
  portlistwindow.style.display = "block";
  portlist.innerHTML = "";
  updateComunicationPortList();
});

connectbtn.addEventListener('click', () => {
  connectionmsg.style.color = "black";
  connectionmsg.innerText = 'STARTING...';
  disconnectbtn.style.display = "none";
  connectedwindow.style.display = "block";
  let curComPort = comunicationport.value;
  let curServerAddress = serveraddress.value;
  let curServerPort = serverport.value;
  let curServerVersion = serverversion.value;
  let curBotName = botname.value;
  curComPort.trim();
  curServerAddress.trim();
  curServerPort.trim();
  curServerVersion.trim();
  curBotName.trim();
  if (curComPort != "" && curServerAddress != "" && curServerPort != "" && curServerPort != "" && curBotName != "") {
    let curConnectionSettings = curComPort + "," + curServerAddress + "," + curServerPort + "," + curServerVersion + "," + curBotName;
    toConnect(curConnectionSettings);
  } else {
    connectionmsg.style.color = "red";
    connectionmsg.innerText = 'INSERT ALL INFO!';
    disconnectbtn.innerHTML = "CLOSE"
    disconnectbtn.style.display = "block";
  }
});

disconnectbtn.addEventListener('click', () => {
  connectedwindow.style.display = "none";
  if (connectbtn.value = "DISCONNECT") {
    toDisconnect();
  }
});