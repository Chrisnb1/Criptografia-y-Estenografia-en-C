# Criptografia y Estenografía en C

Proyecto: Ocultamiento de mensaje encriptado en una imagen. Hecho en C.

## Instrucciones
_Clonar el repositorio_

```
git clone https://github.com/Chrisnb1/Criptografia-y-Estenografia-en-C
```

## Objetivos
* Cifrar un mensaje de texto plano utilizando el algoritmo RSA.
* Ocultar el mensaje cifrado en una imagen. 
* Aislar dicho mensaje de la imagen donde se encuentra oculto y descifrarlo. 

## Programa
Consta de dos funciones:
* Ejecución del algoritmo por consola: se muestra la información de los factores que actúan en el proceso de creación de las claves, el cifrado y el descifrado de un mensaje ingresado por teclado. 
* Creación de archivos (.txt) con información de cada clave y el mensaje.

## Teoría
### Funcionamiento del Algoritmo RSA
RSA es un algoritmo de criptografía asimétrica. Esto quiere decir que opera con dos claves diferentes: Clave Pública y Clave Privada.

### Generación Clave Pública
Se seleccionan dos números primos:

* "p", "q" tal que p ≠ q

Para la primera parte de la clave pública tenemos:

* n = p ∗ q

También se obtiene:

* ∅ = ( p − 1 ) ∗ ( q − 1 )

A esta función se la denomina función Phi o Fi de Euler.

Luego se busca un exponente “e” tal que, cumpla con las siguientes condiciones:

1. Debe ser un numero entero.
2. No ser un factor de n.
3. 1 < e < ∅

La clave pública estaría formada por n y e.

### Cifrado
Utilizando la clave publica podemos cifrar un número M de la siguiente manera:

* C=M^e mod(n)

### Generación Clave Privada
Utilizando el mismo n que la clave pública. Se busca un exponente d tal que, sea el inverso multiplicativo modular entre e y fi:

* d = inv (e, ∅ (n)) 	

### Descifrado
Utilizando la clave privada podemos descifrar un número M de la siguiente manera:

* M=C^e mod(n)
