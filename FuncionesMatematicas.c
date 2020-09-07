//CalcularSuma calcula y devuelve la suma de dos numeros enteros recibidos
int calcularSuma(int primerNumero, int segundoNumero)
{
	return primerNumero + segundoNumero;
}

//CalcularResta calcula y devuelve la resta de dos numeros enteros recibidos
int calcularResta(int primerNumero, int segundoNumero)
{
	return primerNumero - segundoNumero;
}

//CalcularDivision calcula y devuelve el cociente de dos numeros flotantes recibidos (en este caso, casteé previamente los numeros ingresados)
float calcularDivision(float primerNumero, float segundoNumero)
{
	return (primerNumero / segundoNumero);
}

//CalcularMultiplicacion calcula y devuelve el producto de dos numeros enteros recibidos
int calcularMultiplicacion(int primerNumero, int segundoNumero)
{
	return primerNumero * segundoNumero;
}

//CalcularFactorial calcula el factorial de un numero entero recibido
int calcularFactorial(int numero)
{
	int resultado = 1;
	for (numero; 0 < numero; numero--)
	{
		resultado = resultado * numero;
	}
	return resultado;
}