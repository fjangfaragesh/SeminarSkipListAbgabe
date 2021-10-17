//let n = 16777216;
let n = 100000;
let arr = [];


for (let i = 0; i < n; i++) arr.push(i*2)
console.log("geordnetes array gebaut");
    
for (let i = 0; i < n; i++) {
    let i2 = Math.floor(Math.random()*n);
    let buff = arr[i];
    arr[i] = arr[i2];
    arr[i2] = buff;
}
console.log("randomisiert");

let s = "";
for (let i = 0; i < n; i++) {
    s += "\n" + arr[i];
}
console.log("strinifiziert");

document.body.innerHTML = "";
let o = document.createElement("textarea");
o.value = s;
document.body.appendChild(o);

console.log("ausgegeben");
