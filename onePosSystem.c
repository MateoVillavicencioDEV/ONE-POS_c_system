#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

char systemName[10] = "ONE-POS";
int numberOfChashes = 3;
float ivaSystem = 0.12;
int categoryNum = 4;
int quantityProducts = 3;
int maxProducts = 20;
int actualOpenCash = 0;
int maxChashes = 3;
int minProductStock = 2;
int productsWithLowStock = 0;

enum Modules
{
    PRODUCT_MODULE = 1,
    VENTAS_MODULE,
    INVENTARIO_MODULE,
    REPORTES_MODULE,
    CASHES_MODULE,
    FINISH_PROGRAM
};

struct CategoryProductStr
{
    int code;
    char name[20];
};

struct ProductStr
{
    int code;
    char name[20];
    float price;
    bool hasIva;
    float iva;
    int stock;
    struct CategoryProductStr category;
};


struct CategoryProductStr categories[4] = {
    {1, "LIMPIEZA"},
    {2, "BEBIDAS"},
    {3, "CONSUMIBLES"},
    {4, "HOGAR"}
};

struct VentaStr
{
    int code;
    float subtotal;
    float iva;
    float total;
    float discount;
};

struct CashRegisterStr
{
    int code;
    char name[20];
    bool isOpen;
    float montoInicial;
    int numVentas;
    float subtotalVentas;
    float ivaVentas;
    float totalVentas;
    struct VentaStr ventas[10];
};

struct CashRegisterStr cashRegisters[3] = {
        {1, "CAJA 1", false, 0, 0, 0},
        {2, "CAJA 2", false, 0, 0, 0},
        {3, "CAJA 3", false, 0, 0, 0}
};
    
    
struct ProductStr systemProducts[20];

int readInt(char mensaje[]) {
    int valor;
    int validado = 0;

    while (!validado) {
        printf("%s", mensaje);

        if (scanf("%d", &valor) == 1) {
            validado = 1;
        } else {
            printf("Entrada inválida. Debe ser un entero.\n");
        }

        while (getchar() != '\n'); //limpiar repuesta anterior para evitar bucle infinito
    }

    return valor;
}

float readFloat(char mensaje[]) {
    float valor;
    int validado = 0;

    while (!validado) {
        printf("%s", mensaje);

        if (scanf("%f", &valor) == 1) {
            validado = 1;
        } else {
            printf("Entrada inválida. Debe ser un decimal.\n");
        }

        while (getchar() != '\n'); // limpiar buffer SIEMPRE
    }
    

    return valor;
}

void header(const char *title)
{
    int lenTitle = strlen(title);
    for (int i = 0; i < lenTitle + 8; i++)
        printf("*");
    printf("\n*** %s ***\n", title);
    for (int i = 0; i < lenTitle + 8; i++)
        printf("*");
    printf("\n\n");
}

void updateIva(float newIva){

    ivaSystem = newIva;
    int count = 0;
    for(int i = 0; i < quantityProducts; i++){

        if(systemProducts[i].hasIva){

            systemProducts[i].iva = newIva;

            count++;
        }
    }

    printf("%d productos se han actualizado.\n", count);

}

void updateIvaFlow(){

    int optionProductIva;
    printf("El valor de IVA actual es: %0.2f %% \n", ivaSystem * 100);
    
    do
    {
        printf("NOTA: Solo se actualizaran los productos que graven IVA.\n");
        printf("Escoge el valor de IVA deseado:\n");

        printf("1️⃣ \t0%%\n");
        printf("2️⃣ \t12%%\n");
        printf("3️⃣ \t15%%\n");
        printf("4️⃣ \tCANCELAR\n");

        printf("INGRESE LA OPCION: ");
        scanf(" %d", &optionProductIva);

        switch (optionProductIva)
        {
        case 1:
            updateIva(0);
            optionProductIva = 4;
            break;
        case 2:
            updateIva(0.12);
            optionProductIva = 4;
            break;
        case 3:
            updateIva(0.15);
            optionProductIva = 4;
            break;

        case 4:
            break;

        default:
            printf("\nOpcion invalida. Prueba nuevamente.\n");
            break;
        }
    } while (optionProductIva != 4);

}

void showAppName(){
    printf("\n\n");
    printf(" ██████╗ ███╗   ██╗███████╗    ███████╗ ██████╗ ███████╗\n");
    printf("██╔═══██╗████╗  ██║██╔════╝    ██╔══██╗██╔═══██╗██╔════╝\n");
    printf("██║   ██║██╔██╗ ██║█████╗      ██████╔╝██║   ██║███████  \n");
    printf("██║   ██║██║╚██╗██║██╔══╝      ██╔════ ██║   ██║ ╔══╝██  \n");
    printf("╚██████╔╝██║ ╚████║███████╗    ██║     ╚██████╔╝███████╗\n");
    printf(" ╚═════╝ ╚═╝  ╚═══╝╚══════╝    ╚═╝      ╚═════╝ ╚══════╝\n");
    printf("\n");
    printf("\t\t\t%s\n", systemName);
    printf("\n");
}

void mainMenu()
{
    header("MENU MODULOS");

    printf("1️⃣ \tPRODUCTOS\n");
    printf("2️⃣ \tVENTAS\n");
    printf("3️⃣ \tINVENTARIO\n");
    printf("4️⃣ \tREPORTES\n");
    printf("5️⃣ \tCAJAS\n");
    printf("6️⃣ \tSALIR\n");
}

void cashMenu()
{
    // printf("\t---MENU MODULOS---\t\n");
    header("MENU CAJAS ");

    printf("1️⃣ \tABRIR CAJA\n");
    printf("2️⃣ \tCERRAR CAJA\n");
    printf("3️⃣ \tSALIR\n");
    
}
    
void populateProducts(){
    systemProducts[0] = (struct ProductStr){1, "Chocolate", 2.54, true, 0.12, 50, categories[2]};
    systemProducts[1] = (struct ProductStr){2, "Pepsi", 4.54, false, 0, 50, categories[1]};
    systemProducts[2] = (struct ProductStr){3, "Guitig", 0.75, true, 0.12, 50, categories[1]};
}
    

void addNewProduct()
    {
    int validado = 0;
    printf("Hay %d productos registrados.\n", quantityProducts);

    if (quantityProducts < maxProducts)
    { 
        printf("Ingresa el nombre del producto: \n");
        scanf("%19s", systemProducts[quantityProducts].name);

        float price;
        price = readFloat("Ingresa el precio del producto: \n");
    
        systemProducts[quantityProducts].price = price;

        char gravaIva;
        bool hasIva = false;
        char *labelIva = "NO Aplica IVA";
        printf("El producto grava iva? (s/n)\n");
        scanf(" %c", &gravaIva);
        systemProducts[quantityProducts].iva = 0;
        if (gravaIva == 's' || gravaIva == 'S')
        {
            hasIva = true;
            labelIva = "Aplica IVA";
            systemProducts[quantityProducts].iva = ivaSystem;
        }
        systemProducts[quantityProducts].hasIva = hasIva;

        int categoryCode;

        do{

            printf("Escoge la categoria el producto:\n");
            for (int i = 0; i < categoryNum; i++)
            {
                printf("[%d] %s\n", categories[i].code, categories[i].name);
            }
            
    
            // scanf("%d", &categoryCode );
            categoryCode = readInt("Opcion:");
            if(categoryCode < 1 || categoryCode > 4){
                printf("Opcion incorrecta intenta de nuevo \n");

            }

        }while(categoryCode < 1 || categoryCode > 4);

        systemProducts[quantityProducts].category = categories[categoryCode - 1];

        systemProducts[quantityProducts].stock = readInt("Ingresa el stock incial del articulo:");


        printf("El producto fue registrado con exito\n\n");
        printf("Detalles del producto registrado:\nNombre %s \nPrecio $%f (%s) \n", systemProducts[quantityProducts].name, systemProducts[quantityProducts].price, labelIva);
        if(systemProducts[quantityProducts].hasIva){

            printf("IVA: %f %% \n", systemProducts[quantityProducts].iva * 100.00);
    
        }
        printf("categoria: %s\n", systemProducts[quantityProducts].category.name);
        printf("Stock: %d\n\n", systemProducts[quantityProducts].stock);
        systemProducts[quantityProducts].code = quantityProducts + 1;
        quantityProducts += 1;

    }
}

void myProducts(){

    int row, col;
    printf("**LISTA DE PRODUCTOS**\n");
    
    if(quantityProducts <= 0){
        printf("No hay productos registrados. \n");
    }
    
    else{
        printf("Productos Registrados: %d\n", quantityProducts);
            
        printf("════════════════════════════════════════════════════════════════════════════════\n");
        printf("║  Codigo   ║   Nombre   ║   Precio  ║    IVA     ║  Stock  ║   Categoría      ║\n");
        printf("════════════════════════════════════════════════════════════════════════════════\n");

        for(int i = 0; i < quantityProducts; i++){
            
            printf("║    %6d ║ %10s ║   %0.2f    ║   %0.2f%%    ║  %6d    ║   %10s   ║\n",
                systemProducts[i].code,
                systemProducts[i].name,
                systemProducts[i].price,
                systemProducts[i].iva * 100.00,
                systemProducts[i].stock,
                systemProducts[i].category.name
                );
            printf("═════════════════════════════════════════════════════════════════════════════════════\n\n");
            
        }
    }
}

void myProductsLowStock(){

    int row, col;
    if(productsWithLowStock <= 0){
        printf("No hay productos con stock menor o igual a %d unidades. \n", minProductStock);
    } 
    else{
        printf("**LISTA DE PRODUCTOS BAJOS EN STOCK**\n");
        printf("%d Productos con stock bajo!!! \n", productsWithLowStock);
        
        printf("══════════════════════════════════════════════════════════════════\n");
        printf("║  Codigo   ║   Nombre         ║  Stock  ║   Categoría           ║\n");
        printf("══════════════════════════════════════════════════════════════════\n");
        int numLowStockProducts = 0;
        for(int i = 0; i < quantityProducts; i++){
            if (systemProducts[i].stock <= minProductStock){
                numLowStockProducts++;
                printf("║    %6d ║ %14s ║   %d   ║   %10s   ║\n",
                    systemProducts[i].code,
                    systemProducts[i].name,
                    systemProducts[i].stock,
                    systemProducts[i].category.name
                );
                printf("════════════════════════════════════════════════════════════════════════\n\n");
            }
        }   
        
    }
}

void listCashes(){
    printf("--LISTA DE CAJAS--\n");
    for(int i = 0; i < maxChashes; i++){
        printf("[%d] %s \n",cashRegisters[i].code,cashRegisters[i].name);
    }
}

void openCashFlow (){
    if(actualOpenCash != 0){
        printf("Ya existe una caja abierta");
        return;
    }

    int cashSelect;
    float inicialMonto;
    do{
        listCashes();

        cashSelect = readInt("Ingresa a que caja quieres ingresar\n");

        if(cashSelect < 1 ||  cashSelect > maxChashes){
            printf("Opcion no valida.\n");
        }

    }
    while(cashSelect < 1 ||  cashSelect > maxChashes);

    actualOpenCash = cashSelect;
    cashRegisters[actualOpenCash - 1].isOpen = true;
    inicialMonto = readFloat("Ingresa el monto inicial para la caja:\n");
    cashRegisters[actualOpenCash - 1].montoInicial = inicialMonto;
    
    printf("%s abierta existosamente.\n\n", cashRegisters[actualOpenCash - 1].name );
    
}

void showCashResume(int indexCash){
    printf("***RESUMEN DE CAJA***\n");
    printf("Nombre: %s\n", cashRegisters[indexCash].name);
    printf("Monto Inicial: $%0.2f\n", cashRegisters[indexCash].montoInicial);
    printf("Ventas realizdas: %d ventas.\n", cashRegisters[indexCash].numVentas);
    printf("Valor en ventas: $%0.2f\n", cashRegisters[indexCash].totalVentas);
    if(cashRegisters[indexCash].numVentas > 0){
        printf("\n====================DETALLE DE VENTAS==========================");
        for (int i = 0; i < cashRegisters[indexCash].numVentas; i++){
            printf("\n==============================================");
            printf("Venta %d: \nSubtotal:$%0.2f|\tIva:$%0.2f|\tDescuento: $%0.2f\nTotal:$%0.2f\n", 
                cashRegisters[indexCash].ventas[i].code,
                cashRegisters[indexCash].ventas[i].subtotal,
                cashRegisters[indexCash].ventas[i].iva,
                cashRegisters[indexCash].ventas[i].discount,
                cashRegisters[indexCash].ventas[i].total
            );
        }
    } else {
        printf("Sin ventas registradas.\n\n");
    }
}

void closeCashFlow (){
    if(actualOpenCash == 0){
        printf("No existe una caja abierta. \n");
        return;
    }
    printf("%s esta abierta actualmente. Deseas cerrarla? (s/n)\n", cashRegisters[actualOpenCash - 1].name );
    char closeCash;
    int index = actualOpenCash - 1;
    scanf(" %c", &closeCash);
    if (closeCash == 's' || closeCash == 'S')
    {
        showCashResume(index);
        cashRegisters[index].isOpen = false; 
        cashRegisters[index].montoInicial = 0; 
        cashRegisters[index].numVentas = 0; 
        cashRegisters[index].totalVentas = 0;
        memset(cashRegisters[index].ventas, 0, sizeof(cashRegisters[index].ventas)); // limpiar lista de Struct Ventas

        actualOpenCash = 0;
        printf("La caja fue cerrada con exito.\n");
    } 
    
    else {
        printf("Saliendo...\n");
    }
    
}

void reportsFlowModule()
{
    
    int option;
    do
    {
        header("REPORTES");
        printf("1️⃣ \tREPORTE DE INVENTARIO\n");
        printf("2️⃣ \tREPORTE DE VENTAS\n");
        printf("3️⃣\tPRODUCTOS CON STOCK BAJO\n");
        printf("4️⃣ \tSALIR\n");

        option = readInt("INGRESA LA OPCION:\n");
        switch (option)
        {
            case 1:
                header("REPORTE DE INVENTARIO");
                printf("El IVA actual es de: %0.2f\n", ivaSystem * 100);
                myProducts();
                break;
            case 2:
                header("REPORTE DE VENTAS");
                showCashResume(actualOpenCash - 1);
                break;
            case 3:
                header("REPORTE DE VENTAS");
                myProductsLowStock();
                break;
            case 4:
                printf("Saliendo del modulo de reportes...\n");
                break;

            default:
                printf("Opción no valida. Intenta de nuevo.\n");
                break;
        }
    } while (option != 4);

}

void cashFlowModule(){
    int optionCash;
    do
    {
        cashMenu();
        optionCash = readInt("INGRESA LA OPCION:\n");

        switch (optionCash)
        {
        case 1:
            openCashFlow();
            break;

        case 2:
            closeCashFlow();
            break;

        case 3:
            break;

        default:
            printf("Opcion incorrecta, intenta de nuevo.\n");
            break;
        }
        
    } while (optionCash != 3);

}

void saleFlowModule(){
    int productCode;
    int actualStock;
    int quantityProductsSale;
    int indexNewVenta;
    float saleDiscount = 0; 

    if(actualOpenCash == 0) {
        
        printf("Ninguna caja esta abierta\n");
        return;
    };


    header("VENTAS");
    myProducts();

    do{
    
        productCode = readInt("Ingresa el codigo del articulo que se desea vender (0 para cancelar):\n");

        if(productCode == 0) return;

        if (productCode < 0 || productCode > quantityProducts){
            printf("Opcion incorrecta.\n");
        }
    }
    while (productCode < 0 || productCode > quantityProducts);
    
    int indexProduct = productCode - 1;
    actualStock = systemProducts[indexProduct].stock ;
    printf("El stock actual del producto es: %d \n", actualStock);

    do
    {
        quantityProductsSale = readInt("Cuantas unidades se desea vender: \n");

        if(quantityProductsSale > actualStock){
            printf("No hay stock suficiente.\n");
        }
    } 
    while (quantityProductsSale > actualStock && quantityProductsSale > 0);
    
    char userAnswer;
    do
    {
        printf("Deseas aplicar descuento:? (s/n)\n");
        scanf(" %c", &userAnswer);
        if (userAnswer == 's' || userAnswer == 'S')
        {
            do
            {
                saleDiscount = readFloat("Ingresa el porcentaje de descuento(por ejemplo: 5%): \n");
                printf("Se aplicara el %0.2f%% de descuento al total de la venta.\n\n", saleDiscount);
                if (saleDiscount < 0 || saleDiscount > 100)
                {
                    printf("El descuento solo puede estar entre 0%% y 100%%.\n");
                }
                
            } while (saleDiscount < 0 || saleDiscount > 100);
            
        } 

        else if(userAnswer != 's' && userAnswer != 'S' && userAnswer != 'n' && userAnswer != 'N'){
            printf("Opcion no valida.\n");
        }
    } 
    while (userAnswer != 's' && userAnswer != 'S' && userAnswer != 'n' && userAnswer != 'N');
    
    int indexCash = actualOpenCash - 1;
    systemProducts[indexProduct].stock -= quantityProductsSale;
    if(systemProducts[indexProduct].stock <= minProductStock){
        productsWithLowStock++;
        printf("⚠️ PRODUCTO CON STOCK BAJO!!\n");
        Sleep(2500);
    }
    indexNewVenta = cashRegisters[indexCash].numVentas;
    float subtotalVenta = systemProducts[indexProduct].price * quantityProductsSale;
    float sellIva = subtotalVenta*ivaSystem;
    float sellTotal = sellIva + subtotalVenta;
    float totalDiscount = sellTotal * (saleDiscount / 100);
    cashRegisters[indexCash].ventas[indexNewVenta].code = indexNewVenta + 1;
    cashRegisters[indexCash].ventas[indexNewVenta].subtotal = subtotalVenta;
    cashRegisters[indexCash].ventas[indexNewVenta].iva = sellIva;
    cashRegisters[indexCash].ventas[indexNewVenta].discount = totalDiscount;
    cashRegisters[indexCash].ventas[indexNewVenta].total = sellTotal - totalDiscount;

    cashRegisters[indexCash].numVentas += 1;
    cashRegisters[indexCash].subtotalVentas += subtotalVenta;
    cashRegisters[indexCash].ivaVentas += sellIva;
    cashRegisters[indexCash].totalVentas += sellTotal;


    printf("\n====== RESUMEN DE VENTA ======\n");
    printf("Producto: %s\n", systemProducts[indexProduct].name);
    printf("Cantidad vendida: %d\n", quantityProductsSale);
    printf("Precio unitario: $%0.2f\n", systemProducts[indexProduct].price);
    printf("---------------------------------\n");
    printf("Subtotal: $%0.2f\n", subtotalVenta);
    printf("IVA (%0.2f%%): $%0.2f\n", ivaSystem * 100, sellIva);
    printf("Descuento (%0.2f%%): $%0.2f\n",saleDiscount, totalDiscount);
    printf("TOTAL: $%0.2f\n", sellTotal  - totalDiscount);
    printf("---------------------------------\n");
    printf("Venta N°: %d\n", indexNewVenta + 1);
    printf("Total ventas acumuladas: %0.2f\n", cashRegisters[indexCash].totalVentas);
    printf("=================================\n\n");

    Beep(700, 100);
    printf("Venta completada!!!\n\n");
    Sleep(3500);
}

void inventoryFlowModule(){
    int productCode, userAnswer;
    header("INVENTARIO");
    myProducts();

    do
    {
        productCode = readInt("Ingresa el codigo del articulo que deseas cambiar stock (0 para cancelar):\n");

        if(productCode == 0) break;

        else{

            int actualStock = systemProducts[productCode - 1].stock;
            
            printf("Tu stock actual es: %d \n", actualStock);
            
            do
            {
                userAnswer = readInt("Deseas aumentar o disminuir tu stock (0 para aumentar o 1 para disminuir): \n");
            } while (userAnswer != 1 && userAnswer!= 0);
            
            if(userAnswer == 0){

                int addStock = readInt("Ingresa la cantidad a aumentar:\n");
                systemProducts[productCode-1].stock += addStock;

            }

            else{
                int substStock;
                
                do{
                    substStock = readInt("Ingresa la cantidad a disminuir:\n");

                    if(actualStock < substStock){
                        printf("Disminucion de stock invalida\n");
                    }
                }
                while(actualStock < substStock );

                systemProducts[productCode-1].stock -= substStock;
            }
            
            printf("Stock del producto actualizado a: %d\n\n", systemProducts[productCode - 1].stock);
        }

    } while (productCode == 0 || (productCode < 1 || productCode > quantityProducts) );

}

void productFlowModule(){
    
    int optionProductMenu;
    
    do
    {
        header("MENU PRODUCTOS");
        
        printf("1️⃣ \tREGISTRA PRODUCTOS\n");
        printf("2️⃣ \tMIS PRODUCTOS\n");
        printf("3️⃣ \tEDITAR VALOR DE IVA\n");
        printf("4️⃣ \tSALIR\n");
        
        printf("INGRESE LA OPCION: ");
        scanf(" %d", &optionProductMenu);
        
        switch (optionProductMenu)
        {
            case 1:
            addNewProduct();
            break;
            case 2:
            myProducts();
            break;
            case 3:
            updateIvaFlow();
            break;
            case 4:
            
            break;
            
            default:
            printf("\nOpcion invalida. Prueba nuevamente.\n");
            break;
        }
    } while (optionProductMenu != 4);
}

void exitApp(){
    printf("\n\n====================GRACIAS POR USAR====================");
    showAppName();
    printf("\nDevelopers:\n\t💻 Mateo Villavicencio.\n\t💻 Marcos Quimba");
    printf("\n===========================\n");
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    populateProducts();

    struct CashRegisterStr cashRegisters[3] = {
        {1, "CAJA 1"},
        {2, "CAJA 2"},
        {3, "CAJA 3"}};
    
    int optionMainMenu, opcionCashMenu;
    showAppName();
    do
    {
        mainMenu();

        optionMainMenu = readInt("INGRESE LA OPCION: \n");
        
        switch (optionMainMenu)
        {
            case PRODUCT_MODULE:
                // Beep(700, 100);
                productFlowModule();
                break;
            case VENTAS_MODULE:
                saleFlowModule();
                break;
            case INVENTARIO_MODULE:
                inventoryFlowModule();
                break;
            case REPORTES_MODULE:
                reportsFlowModule();
                break;
            case CASHES_MODULE:
                cashFlowModule();
                break;
            case FINISH_PROGRAM:
                exitApp();
                break;
            
            default:
            printf("\nOpcion invalida. Prueba nuevamente.");
            break;
        }
        
    } while (optionMainMenu != FINISH_PROGRAM);
    
    return 0;
}