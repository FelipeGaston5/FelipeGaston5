//##############==Variaveis e tipos de dados em TypeScript==##############
// Number.
let num : number = 10;
console.log(num);

// String.
let str : string = "hello";
console.log(str);

// Booleano.
let bool : boolean = true;
console.log(bool);

// Array de números.
let list : number[] = [1,2,3];
console.log(list);

// Ou seja, o mesmo que o de cima, mas com a sintaxe diferente.
let list2 : Array<number> = [1,2,3];
console.log(list2);

// Tuple em TypeScript. Com 'nome' e 'idade' como propriedades/chave da tuple.
let obj = {nome: "Felipe", idade: 19};
console.log(obj);

//Array de tuplas.
let listNomes : Array<any> = [
    {nome : "Felipe", idade : 19},
    {nome : "João",idade : 20},
    {nome : "Maria", idade : 21}
]
console.log(listNomes);
console.log(listNomes[0]) //Felipe 19
console.log(listNomes[1].idade) //20


//##############==Funções em TypeScript==##############

//Função simples que retorna um número.
function medF(a: number, b:number) : number {
    return (a + b) / 2;
}



let resultado1 = medF(10, 20);
console.log(resultado1); //15

//Arrow function que retorna um número.

let medA = (a: number, b:number) : number => {
    return (a + b) / 2;
};

//Outras  formas de se escrever a função acima.
//let medA = (a: number, b:number) : number => (a + b) / 2;
//let medA = (a: number, b:number) => (a + b) / 2;    //Sem o tipo de retorno.
//let medA = (a, b) => (a + b) / 2;                   //Sem o tipo de retorno e sem o tipo dos parâmetros.


let resultado2 = medA(10, 20);
console.log(resultado2); //15

let printar = () => console.log("Hello World!");
printar(); //Hello World!

//##############==Condicionais em TypeScript==##############

const hora : number = 10; //Constante, não pode ser alterada.

console.log(hora < 18 ? "Bom dia!" : "Boa noite!"); //Bom dia!
//O operador ternário é uma forma de simplificar o if/else.







// ===========================================================================================

//É nescessario tranformar o .ts em .js para que o código de TypeScript funcione.


