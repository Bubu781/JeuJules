const express = require('express');
const http = require('http');
const WebSocket = require('ws');
const net = require('net');
const app = express();

const center = 10;
const taille = 20;
check_around = (labyrinthe, x, y)=>{
    let sum = 0, pos1, pos2, pos3, pos4;
    if(x-1 < 0) pos1 = 1;
    else pos1 = labyrinthe[x-1][y];
    if(x+1==taille) pos2=1;
    else pos2 = labyrinthe[x+1][y];
    if(y-1 < 0) pos3 = 1;
    else pos3 = labyrinthe[x][y-1];
    if(y+1==taille) pos4=1;
    else pos4 = labyrinthe[x][y+1];
    sum = pos1+pos2+pos3+pos4;
    if(sum != 3) return false;
    else return true;
}
createTab = () =>{
    let labyrinthe = new Array(taille);
    for(let i = 0; i < taille; i++) labyrinthe[i] = new Array(taille);
    let x = center, y = center;
    let cas = -1, holes = 0;
    let turn = 0;
    for(let i = 0; i < taille; i++)
        for(let j = 0; j < taille; j++)
            labyrinthe[i][j] = 1;
    while(x != 0 && x != taille - 1 &&
        y != 0 && y != taille - 1){
        if(Math.floor(Math.random()*2) == 1){ //modifier x
            if(Math.floor(Math.random()*2) == 1){
                if(labyrinthe[x-1][y] != 0 && check_around(labyrinthe, x-1, y) && (cas != 0 || turn % 3 == 0)){
                    x--;
                    cas = 0;
                }
            }else if(labyrinthe[x+1][y] != 0 && check_around(labyrinthe, x+1, y) && (cas != 1 || turn % 3 == 0)){
                x++;
                cas = 1;
            }
        }else{ //modifier y
            if(Math.floor(Math.random()*2) == 1){
                if(labyrinthe[x][y-1] != 0 && check_around(labyrinthe, x, y-1) && (cas != 2 || turn % 3 == 0)){
                    y--;
                    cas = 2;
                }
            }else if(labyrinthe[x][y+1] != 0 && check_around(labyrinthe, x, y+1) && (cas != 3 || turn % 3 == 0)){
                y++;
                cas = 3;
            }
        }
        turn++;
        labyrinthe[x][y] = 0;
        if(turn > taille * taille){
            createTab();
            break;
        }
    }
    while(holes < taille*taille/3){
        x = Math.floor(Math.random()*taille);
        y = Math.floor(Math.random()*taille);
        if(labyrinthe[x][y] == 1 && check_around(labyrinthe, x, y)==1 && x != 0 && x != taille - 1 && y != 0 && y != taille - 1){
            labyrinthe[x][y] = 0;
            holes++;
        }
    }
    for(let i = center - 2; i < center + 2; i++)
        for(let j = center - 2; j < center + 2; j++)
            labyrinthe[i][j] = 0;
    return labyrinthe;
}
let letter = "A";
let clients = [];
net.createServer(function(socket){
    socket.write("P"+letter);
    socket.pseudo = letter;
    console.log("connected", socket.pseudo);
    clients.push(socket);
    if(letter == "A")
        letter = "B";
    else{
        let labyrinthe = createTab();
        for(let i = 0; i < taille; i++){
            let txt = "I";
            for(let j = 0; j < taille; j++)
                txt = txt.concat(labyrinthe[i][j]);
            clients.forEach(client =>{
                client.write(txt);
                console.log(txt);
                console.log("send map", client.pseudo);
            });
        }
        let x1 = Math.floor(Math.random()*4) - 2 + center;
        let y1 = Math.floor(Math.random()*4) - 2 + center;
        let x2 = Math.floor(Math.random()*4) - 2 + center;
        let y2 = Math.floor(Math.random()*4) - 2 + center;
        do{
        x1 = Math.floor(Math.random()*4) - 2 + center;
        y1 = Math.floor(Math.random()*4) - 2 + center;
        x2 = Math.floor(Math.random()*4) - 2 + center;
        y2 = Math.floor(Math.random()*4) - 2 + center;
        }while(x1 == x2 && y1 == y2);
        clients.forEach(client =>{
            if(client.pseudo == "A")
                client.write("N"+client.pseudo+String.fromCharCode(x1)+String.fromCharCode(y1));
            else
                client.write("N"+client.pseudo+String.fromCharCode(x2)+String.fromCharCode(y2));
        });
    }
    socket.on("data",(data)=>{
        let str = "";
        console.log(data)
        for(let i = 0; i < 5; i++){
            str = str.concat(String.fromCharCode(data[i]));
        }
        console.log(str)
        clients.forEach(client=>{
            if(client.pseudo != socket.pseudo){
                client.write("N"+socket.pseudo+String.fromCharCode(data[1])+String.fromCharCode(data[2]));
                console.log("send pos", socket.pseudo);
            }
        })
    });
}).listen(3000);

/*
//initialize a simple http server
const server = http.createServer(app);

//initialize the WebSocket server instance
const wss = new WebSocket.Server({ server });
wss.on('connection', (ws) => {
    //connection is up, let's add a simple simple event
    for(let i = 0; i < taille; i++)
        for(let j = 0; j < taille; j++)
            ws.on("N"+i+j, ()=>{
                wss.clients.forEach(client=>{
                    client.send("N"+client.pseudo+i+j);
                    console.log("send pos", client.pseudo);
                })
            });
});



//start our server
server.listen(process.env.PORT || 3000, () => {
    console.log(`Server started on port ${server.address().port} :)`);
});*/

module.exports = app;