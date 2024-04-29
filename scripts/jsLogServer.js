const net = require("net");
net.createServer((socket) => {
    console.log("new connection", socket.remoteAddress, socket.remotePort, socket.remoteFamily);
    socket
        .on("data", (data) => {
            process.stdout.write(data.toString("utf-8"));
        })
        .on("close", (error) => console.log("new disconnect", error))
        .on("error", () => console.log("errorma"));
}).listen(3080, () => { console.log("listening"); });