import * as express from 'express';
import * as http from 'http';
import * as WebSocket from 'ws';

const app = express();

const center = 10;
const taille = 20;
//initialize a simple http server
const server = http.createServer(app);

//initialize the WebSocket server instance
const wss = new WebSocket.Server({ server });
let letter = "A";
wss.on('connection', (ws) => {
    
    ws.send("P"+letter);
    ws.pseudo = letter;
    if(letter === "A"){
        letter = "B";
    }else{
        let labyrinthe = createTab();
        let txt = "";
        for(let i = 0; i < taille; i++)
            for(let j = 0; j < taille; j++)
                txt = txt.concat(labyrinthe[i][j]);
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
        wss.clients.forEach(client =>{
            client.send("I"+txt);
            if(client.pseudo == "A")
                client.send("N"+client.pseudo+x1+y1);
            else
                client.send("N"+client.pseudo+x2+y2);
        });
    }
    //connection is up, let's add a simple simple event
    for(let i = 0; i < taille; i++)
        for(let j = 0; j < taille; j++)
            ws.on("N"+i+j, ()=>{
                wss.clients.forEach(client=>{
                    client.send("N"+client.pseudo+i+j);
                })
            });
});

//start our server
server.listen(process.env.PORT || 8999, () => {
    console.log(`Server started on port ${server.address().port} :)`);
});

createTab = () =>{
    let labyrinthe = [[],[]];
    let x = center, y = center;
    let cas = -1, holes = 0;
    let turn = 0;
    for(let i = 0; i < taille; i++){
        for(let j = 0; j < taille; j++)
            labyrinthe[i][j] = 1;
    }
    while(x != 0 && x != taille - 1 &&
        y != 0 && y != taille - 1){
        if(Math.floor(Math.random()*2)){ //modifier x
            if(Math.floor(Math.random()*2)){
                if(labyrinthe[x-1][y] != 0 && check_around(x-1, y) && (cas != 0 || turn % 3 == 0)){
                    x--;
                    cas = 0;
                }
            }else if(labyrinthe[x+1][y] != 0 && check_around(x+1, y) && (cas != 1 || turn % 3 == 0)){
                x++;
                cas = 1;
            }
        }else{ //modifier y
            if(Math.floor(Math.random()*2)){
                if(labyrinthe[x][y-1] != 0 && check_around(x, y-1) && (cas != 2 || turn % 3 == 0)){
                    y--;
                    cas = 2;
                }
            }else if(labyrinthe[x][y+1] != 0 && check_around(x, y+1) && (cas != 3 || turn % 3 == 0)){
                y++;
                cas = 3;
            }
        }
        turn++;
        labyrinthe[x][y] = 0;
        if(turn > taille * taille){
            create_lab();
            return;
        }
    }
    while(holes < taille*taille/3){
        x = Math.floor(Math.random()*taille);
        y = Math.floor(Math.random()*taille);
        if(labyrinthe[x][y] == 1 && check_around(x, y)==1 && x != 0 && x != taille - 1 && y != 0 && y != taille - 1){
            labyrinthe[x][y] = 0;
            holes++;
        }
    }
    for(let i = center - 2; i < center + 2; i++)
        for(let j = center - 2; j < center + 2; j++)
            labyrinthe[i][j] = 0;
    return labyrinthe;
}