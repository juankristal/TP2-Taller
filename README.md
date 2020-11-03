# Taller de Programacion [75.42] - TP2

**Nombre: Juan Ignacio Kristal**

**Padron: 99779**

**Repositorio: https://github.com/juankristal/TP2-Taller**

**Cuatrimestre: 2C 2020**

1. **[Modelo](#Modelo)**

2. **[Parseo de archivos BPF](#BPFP)**

3. **[Verificacion de archivos BPF](#BPFV)**

4. **[Threads](#Threads)**

## Modelo <a name="Modelo"></a>

Se requeria implementar un modelo el cual parsee un grupo de archivos BPF. Dicho modelo fue dividido en partes. Para lograr una mayor performance se utilizaron threads para procesar multiples archivos a la vez.

El proceso fue dividido en tres partes. Parseo del archivo, verificacion del archivo y manejo de archivos concurrentemente.

Para el parseo de archivos se opto por un objeto ParserBPF el cual lee el archivo y crea objetos Linea con la informacion organizada para un uso mas sencillo.

Dichas lineas son luego procesadas por un Worker el cual genera y conecta un Grafo en base a dicho procesamiento. Es entonces donde empieza el proceso de verificacion donde el Grafo utiliza el algoritmo de DFS para verificar el estado del archivo.

Finalmente para generar concurrencia se utilizo Threads, un objeto ProcesadorArchivos que se encarga de procesar archivos entregados por un Enviador y se los envia a un Recibidor. Ambas operaciones son criticas y fueron lockeadas usando mutex para hacerlas atomicas. 

![Imagen 1](img/clases.png?raw=true)

_Imagen 1. Clases del modelo_

## Parseo de archivos BPF <a name="BPFP"></a>

Para parsear los archivos como fue indicado antes se implemento un parser el cual dividia cada linea en su label, opcode y labels vinculados. Todo esto fue almacenado en un contenedor Linea el cual tiene ciertos valores por defecto. Una linea vacia es irrelevante para el verificador y por lo tanto el parser la inicializa en un estado cuyo label es "EMPTY". Dicho label es luego utilizado por el verificador para filtrarlas.

Ademas, para lineas que no tienen salto o tienen un salto condicional, se agrega un linked label llamado "NEXT" el cual indica al Worker que debe unir dicha linea con la proxima.

Finalmente el parser solo parsea de a una linea a la vez, el Worker se encarga luego de almacenar todas las lineas relevantes en una lista que luego se usara para la verificacion.

## Verificacion de archivos BPF <a name="BPFV"></a>

Para la verificacion de los archivos existen tres posibles estados. Un archivo es invalido si tiene ciclos o si tiene lineas sin utilizar (excluyendo lineas vacias). De lo contrario es valido. Los tres estados fueron representados con un valor numerico el cual es informado al objeto relevante una ves terminado el procesamiento.

Para detectar ciclos se represento al archivo como un grafo. Utilizando la lista de lineas previamente parseada se genera un grafo dirigido al cual se le aplica luego DFS para encontrar ciclos. Dicho DFS devuelve si hay loops y luego se verifica si todos los nodos fueron visitados para ver si hay lineas sin utilizar.

Para poder generar el grafo fue necesario mantener un mapa que vincule a un label con su numero de linea. El Worker antes de generar el grafo y utilizando la lista de lineas previamente construida, genera dicho mapa. Con ese vinculo el grafo es conectado revisando los labels vinculados. Ademas, se utilizo un nodo 0 el cual representa al fin de la ejecucion (todos los ret apuntan a el).


## Threads <a name="Threads"></a>

Para el manejo de Threads se crearon ambas clases Thread y ProcesadorArchivos siendo la ultima clase hija de Thread.

El Procesador tiene como atributos los monitores Enviador y Recibidor y es starteado en el momento que es instanciado. Al correr se instancia un Worker y un buffer en donde se iran guardando los diferentes nombres de archivos a ser procesados (previamente solicitados al Enviador). Dicho Worker procesara el archivo y le enviara el nombre y el estado final al Recibidor.

Las dos operaciones criticas de la ejecucion son la solicitud de archivo y la entrega para el Enviador y Recibidor respectivamente. Utilizando un unique_lock se evitaron las Race Conditions.

Finalmente el Enviador imprimira el resultado final ordenando los archivos y sus estados correspondientes segun fue indicado en la consigna.