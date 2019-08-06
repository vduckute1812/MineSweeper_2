const {spawn} = require('child_process');
const  TIMEOUT = 200; //10 milliseconds
const  MAX_TURN = 1000; //
const  MAP_WIDTH = 14400; //
const  MAX_HEIGHT = 9600; //
const  INIT_MAP = 10101; //
const args = process.argv;
if (args.length < 5)
{
    console.log("cmd: 'node main.js path_gameserver path_mybot path_rival'")
    process.exit();
}
function spawnProcess(path){
    if(path.indexOf(".exe")>-1){
        return spawn(path);
    }else if(path.indexOf(".py")>-1){
        return spawn('python',[path]); 
    }else if(path.indexOf(".jar")>-1){
        return spawn('java -jar ',[path]); 
    }else {
        return spawn(path)
    }
}
const gameServer = spawn(args[2],['LogTest\\']);
const myBot = spawnProcess(args[3]);
const rival = spawnProcess(args[4]);

var myBotOut = "E101";
var rivalOut = "E201";
var myLog = "First package!!";
var isInit = false;

myBot.stdout.on('data', (data) => {
    data = data.toString().trim().replace(/\r?\n|\r/g, "-");
    console.log('Bot A send:\'%s\'',data);
    myBotOut = data;
});

myBot.stderr.on('data', (data) => {
    data = data.toString().trim().replace(/\r?\n|\r/g, "|");
    console.log('Bot A log:\'%s\'',data);
    myLog = data;
});
//
rival.stdout.on('data', (data) => {
    data = data.toString().trim().replace(/\r?\n|\r/g, "-");
    //console.log('Bot B send:\'%s\'',data);
    rivalOut = data
});


gameServer.stdout.on('data', (data) => {

    console.log("Server send:\'%s\'",data);
    stringData = data.toString().trim();

    if(!isInit && stringData.startsWith("START"))
    {	setTimeout(function (){
        myBot.stdin.write(MAP_WIDTH+' ' + MAX_HEIGHT+' '  + MAX_TURN+' ');	
        rival.stdin.write(MAP_WIDTH+' ' + MAX_HEIGHT+' '  + MAX_TURN+' ');
        gameServer.stdin.write(myBotOut+'#'+rivalOut+"#Init map infos\n");
        isInit = true;
    },2000);
    }
    else if(!stringData.startsWith("END"))
    {
        try{
            myBot.stdin.write(data+'\n');
        }catch (err)
        {
            myLog="Something went wrong with my bot"
        }
        try{
            rival.stdin.write(data+'\n');
        }catch (err)
        {
            myLog="Something went wrong with my rival"
        }
	   
        //send bot's info to server
        setTimeout(function () {		
            console.log("SendToSV: "+myBotOut+'#'+rivalOut+"#"+myLog+"\n");
            gameServer.stdin.write(myBotOut+'#'+rivalOut+"#"+myLog+"\n");
            myLog ="-------";
            myBotOut  = "E101";
            rivalOut = "E201";
        },TIMEOUT);
    }
    else{
        console.log('Game end: %s',stringData); 
    }
});
gameServer.stderr.on('data', (data) => {
    console.log('Server err log: \'%s\'\n',data);
});
gameServer.on('close', (code) => {
    console.log('The end game ------> %s',code); //return 0 1 3 = lose, draw, win 
    process.exit();
});