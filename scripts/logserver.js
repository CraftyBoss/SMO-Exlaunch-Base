const net = require("net");

for (let i = 3080; i < 3083; i++)
	net.createServer((socket) => {
	  //console.log("new connection");
	  socket.on("data", (data) => {
	    process.stdout.write(data.toString("utf-8"));
	  }).on("close", (error) => console.log("new disconnect", error)).on("error", () => console.log("errorma"));
	}).listen(i, () => {
	  console.log("listening");
	});
