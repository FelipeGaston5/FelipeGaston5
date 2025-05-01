//##############==Variaveis e tipos de dados em TypeScript==##############
// Number.
var num = 10;
console.log(num);
// String.
var str = "hello";
console.log(str);
// Booleano.
var bool = true;
console.log(bool);
// Array de números.
var list = [1, 2, 3];
console.log(list);
// Ou seja, o mesmo que o de cima, mas com a sintaxe diferente.
var list2 = [1, 2, 3];
console.log(list2);
// Tuple em TypeScript. Com 'nome' e 'idade' como propriedades/chave da tuple.
var obj = { nome: "Felipe", idade: 19 };
console.log(obj);
//Array de tuplas.
var listNomes = [
    { nome: "Felipe", idade: 19 },
    { nome: "João", idade: 20 },
    { nome: "Maria", idade: 21 }
];
console.log(listNomes);
console.log(listNomes[0]); //Felipe 19
console.log(listNomes[1].idade); //20
//##############==Funções em TypeScript==##############
//Função simples que retorna um número.
function medF(a, b) {
    return (a + b) / 2;
}
var resultado1 = medF(10, 20);
console.log(resultado1); //15
//Arrow function que retorna um número.
var medA = function (a, b) {
    return (a + b) / 2;
};
//Outras  formas de se escrever a função acima.
//let medA = (a: number, b:number) : number => (a + b) / 2;
//let medA = (a: number, b:number) => (a + b) / 2;    //Sem o tipo de retorno.
//let medA = (a, b) => (a + b) / 2;                   //Sem o tipo de retorno e sem o tipo dos parâmetros.
var resultado2 = medA(10, 20);
console.log(resultado2); //15
var printar = function () { return console.log("Hello World!"); };
printar(); //Hello World!
// ===========================================================================================
//É nescessario tranformar o .ts em .js para que o código de TypeScript funcione.
