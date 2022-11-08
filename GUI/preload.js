const { contextBridge, ipcRenderer, remote, shell, autoUpdater } = require('electron');

contextBridge.exposeInMainWorld('electron', { ipcRenderer, remote, shell });

const IPC_CHANNEL = 'ipc';

ipcRenderer.on(IPC_CHANNEL, (event, data) => {
    let ipcData = data;
    let dataSettingsSplitted = ipcData.split(",");
    if (dataSettingsSplitted[0] == "ADD_PORT") {
        var portButton = document.createElement("button");
        portButton.className = "medium-button port-select";
        portButton.innerText = dataSettingsSplitted[1] + " (" + dataSettingsSplitted[2] + ")";
        portButton.value = dataSettingsSplitted[1];
        portButton.style.marginLeft = "20px";
        portButton.style.display = "block";
        portButton.style.marginBottom = "5px";
        portlist.appendChild(portButton);
    }
    if (dataSettingsSplitted[0] == "JSON_SETTINGS_CREATING") {
        connectionmsg.innerText = 'SAVING SETTINGS...';
    }
    if (dataSettingsSplitted[0] == "JSON_SETTINGS_CREATED") {
        connectionmsg.innerText = 'SETTINGS SAVED!';
        ipcRenderer.send(IPC_CHANNEL, "CLIENT_READY");
    }
    if (dataSettingsSplitted[0] == "JSON_SETTINGS_NOT_CREATED") {
        connectionmsg.style.color = "red";
        connectionmsg.innerText = 'SAVING SETTINGS ERROR!';
        disconnectbtn.style.display = "block";
        disconnectbtn.innerText = "CLOSE";
    }
    if (dataSettingsSplitted[0] == "CONFIG") {
        serveraddress.value = dataSettingsSplitted[1];
        serverport.value = dataSettingsSplitted[2];
        serverversion.value = dataSettingsSplitted[3];
        botname.value = dataSettingsSplitted[4];
    }
    if (dataSettingsSplitted[0] == "BOT_STARTING") {
        connectionmsg.style.color = "black";
        connectionmsg.innerText = 'CHECKING...';
        disconnectbtn.style.display = "none";
    }
    if (dataSettingsSplitted[0] == "BOT_STARTED") {
        connectionmsg.style.color = "green";
        connectionmsg.innerText = 'STARTED!';
        disconnectbtn.style.display = "block";
        disconnectbtn.innerText = "DISCONNECT";
    }
});

ipcRenderer.send(IPC_CHANNEL, "LOAD_CONFIG");