/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

float manual_fabs(float f) {
    return (f < 0) ? -f : f;
}

long manual_roundf(float f) {
    return (long)(f + 0.5f);
}

char* floatParaString(float numero, char *bufferDisplay) {
    char *ptr = bufferDisplay;
    long parteInteiraAbs;
    long parteDecimalAbs;
    long divisor;

    if (numero < 0) {
        *ptr++ = '-';
        numero = manual_fabs(numero);
    }

    long numeroMultiplicado = manual_roundf(numero * 100.0f);

    parteInteiraAbs = numeroMultiplicado / 100;
    parteDecimalAbs = numeroMultiplicado % 100;

    if (parteInteiraAbs == 0) {
        *ptr++ = '0';
    } else {
        divisor = 1;
        long tempInt = parteInteiraAbs;
        while (tempInt >= 10) {
            tempInt /= 10;
            divisor *= 10;
        }
        while (divisor > 0) {
            *ptr++ = (parteInteiraAbs / divisor) % 10 + '0';
            divisor /= 10;
        }
    }

    *ptr++ = ',';

    *ptr++ = (parteDecimalAbs / 10) + '0';
    *ptr++ = (parteDecimalAbs % 10) + '0';

    *ptr = '\0';

    return bufferDisplay;
}
