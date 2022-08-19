const { app, BrowserWindow } = require('electron')

// 热加载
try {
    require('electron-reloader')(module, {});
} catch (_) { }
const createWindow = () => {
    const win = new BrowserWindow({
        width: 800,
        height: 800
    })

    win.loadFile('./src/index.html')
}

app.whenReady().then(() => {
    createWindow()
})