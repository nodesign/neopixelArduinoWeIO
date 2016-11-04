var cnt = 0;
var etat = false;

function setup() {
    // canvas size in pixels
    createCanvas(800, 600);
    // always put some frame rate, don't make suffer cpu or websockets
    frameRate(12);

}

function draw() {
    background(0);
    
    if (etat) {
        if (cnt<255) cnt+=3; else etat = false;
    } else {
        if (cnt>0) cnt-=3; else etat = true;
    }       
    
    fill(cnt);
    ellipse(width/2.0, height/2.0, 100,100);
   // writeToAllLeds(cnt,cnt,cnt);
    writeToLed(10, cnt,cnt,cnt);
}

function writeToLed(led, r,g,b) {
    var data = [led, r,g,b];
    genericMessage("writeToLed", data);
}

function writeToAllLeds(r,g,b) {
    var data = [r,g,b];
    genericMessage("writeToAllLeds", data);
}