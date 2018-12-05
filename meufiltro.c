#include "meufiltro.h"
#include <time.h>


void inicializarWidgetsMeuFiltro() {
	//widgets das opcoes de filtro
	widgetTituloTamLadrilho = gtk_label_new("Tamanho do ladrilho");
	widgetTamanhoLadrilho = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 30, 2);
	
	widgetTituloAnguLadrilho = gtk_label_new("Ângulo do ladrilho");
	widgetAnguloLadrilho = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 89, 1);
	
	widgetTituloTamanhoBorda = gtk_label_new("Tamanho da borda");
	widgetTamanhoBorda = gtk_spin_button_new_with_range (0, 5, 1);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widgetTamanhoBorda), 2);

	widgetTituloOrientacaoLadrilho = gtk_label_new("Ativa opções de orientação do Ladrilho");
	widgetRadio = gtk_radio_button_new(NULL);
	widgetRadioAleatorio = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(widgetRadio), "Aleatório");
	widgetRadioGradiente = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(widgetRadio), "Gradiente");
	widgetRadioFixo = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(widgetRadio), "Fixo");

	//Botão de cor
	widgetCor = gtk_color_button_new();

	//Titulo cor de fundo
    	widgetTituloCorFundo = gtk_label_new("Cor de fundo");

	//Botão on/off rotação
	widgetOnOffRotacao = gtk_switch_new();

	//Titulo posição aleatória do ladrilho
	widgetTituloPosAleatoriaLadrilho = gtk_label_new("Ativa a posição aleatória do Ladrilho");

	//Botão on/off posição aleatória do ladrilho
	widgetOnOffPosLadrilho = gtk_switch_new();

	//Chama a função aplicar quando mexe no slide da rotação.
	g_signal_connect(G_OBJECT(widgetTamanhoLadrilho), "value-changed", G_CALLBACK(funcaoAplicar), NULL);
	g_signal_connect(G_OBJECT(widgetAnguloLadrilho), "value-changed", G_CALLBACK(funcaoAplicar), NULL);
	g_signal_connect(G_OBJECT(widgetTamanhoBorda), "value-changed", G_CALLBACK(funcaoAplicar), NULL);
	g_signal_connect(G_OBJECT(widgetOnOffRotacao), "state-set", G_CALLBACK(funcaoAplicar), NULL);
	g_signal_connect(G_OBJECT(widgetOnOffPosLadrilho), "state-set", G_CALLBACK(funcaoAplicar), NULL);
	g_signal_connect(G_OBJECT(widgetRadioAleatorio), "toggled", G_CALLBACK(funcaoAplicar), NULL);
	g_signal_connect(G_OBJECT(widgetRadioGradiente), "toggled", G_CALLBACK(funcaoAplicar), NULL);
	g_signal_connect(G_OBJECT(widgetCor), "color-set", G_CALLBACK(funcaoAplicar), NULL);

	//Chama a funcão de habilitar/desabilitar os Widgets. 
	g_signal_connect(G_OBJECT(widgetOnOffRotacao), "state-set", G_CALLBACK(ativaWidgets), NULL);
	g_signal_connect(G_OBJECT(widgetRadioAleatorio), "toggled", G_CALLBACK(ativaWidgets), NULL);
	g_signal_connect(G_OBJECT(widgetRadioGradiente), "toggled", G_CALLBACK(ativaWidgets), NULL);
}

void adicionarWidgetsMeuFiltro(GtkWidget *container) {

	//Dbox para widgets do lado direito; Ebox para os do lado esquerdo; e vbox recebe os Dbox e Ebox.
	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15); 
	GtkWidget *Dbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	GtkWidget *Ebox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 3);
	gtk_container_set_border_width(GTK_CONTAINER(Dbox), 3);
	gtk_container_set_border_width(GTK_CONTAINER(Ebox), 3);
	
	gtk_container_add(GTK_CONTAINER(vbox), Ebox);
	gtk_container_add(GTK_CONTAINER(vbox), Dbox);
	gtk_container_add(GTK_CONTAINER(container), vbox);
	
	//Deixa alinhado igualmente e horizontalmente o Dbox (também na vertical) e Ebox
	gtk_box_set_homogeneous(GTK_BOX(vbox), TRUE); 
	gtk_box_set_homogeneous(GTK_BOX(Dbox), TRUE); 

	//========== Tíulos e barras de rolagem do lado direito ==========
	gtk_container_add(GTK_CONTAINER(Dbox), widgetTituloTamLadrilho);
	gtk_container_add(GTK_CONTAINER(Dbox), widgetTamanhoLadrilho);

	gtk_container_add(GTK_CONTAINER(Dbox), widgetTituloAnguLadrilho);
	gtk_container_add(GTK_CONTAINER(Dbox), widgetAnguloLadrilho);
	
	gtk_container_add(GTK_CONTAINER(Dbox), widgetTituloTamanhoBorda);
    	gtk_container_add(GTK_CONTAINER(Dbox), widgetTamanhoBorda);

	//========== Títulos e botões do lado esquerdo ==========
	
	//Titulo orientação do ladrilho 
	gtk_container_add(GTK_CONTAINER(Ebox), widgetTituloOrientacaoLadrilho);

	//Botão on/off rotacao
	gtk_container_add(GTK_CONTAINER(Ebox), widgetOnOffRotacao);

	//Radio button 
	gtk_container_add(GTK_CONTAINER(Ebox), widgetRadioAleatorio);
	gtk_container_add(GTK_CONTAINER(Ebox), widgetRadioGradiente);
	gtk_container_add(GTK_CONTAINER(Ebox), widgetRadioFixo);

	//Titulo cor de fundo
	gtk_container_add(GTK_CONTAINER(Ebox), widgetTituloCorFundo);

	//Botão da cor
	gtk_container_add(GTK_CONTAINER(Ebox), widgetCor);

	//Título da janela do botão de cor
	gtk_color_button_set_title(GTK_COLOR_BUTTON(widgetCor), "Cor de fundo");

        //Titulo posição aleatória do ladrilho
	gtk_container_add(GTK_CONTAINER(Ebox), widgetTituloPosAleatoriaLadrilho);

        //Botão on/off posição aleatória do ladrilho
	gtk_container_add(GTK_CONTAINER(Ebox), widgetOnOffPosLadrilho);
		
	//Inicia o Radio button fixo como on
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widgetRadioFixo), 1);
	
	//======================================================

	//Inicia desativado as opções do ângulo do ladrilho, Gradiente, aleatória e Fixo
	gtk_widget_set_sensitive(widgetRadioGradiente, FALSE);
	gtk_widget_set_sensitive(widgetRadioAleatorio, FALSE);
	gtk_widget_set_sensitive(widgetRadioFixo, FALSE);	
	gtk_widget_set_sensitive(widgetAnguloLadrilho, FALSE);	
}

Imagem meuFiltro(Imagem origem) {
	
	//================ Variáveis ===================
	int i, j; // Usadas para posição em relação as matrizes das imagens.
	Imagem destino = alocarImagem(origem);
	int tamLadri = (int) gtk_range_get_value(GTK_RANGE(widgetTamanhoLadrilho)); //tamanho do ladrilho

	//Canais de cores
	int ch1 = 0, ch2 = 1, ch3 = 2;
	
	//rot armazena o estado do botão da orientação do ladrilho
	int rot = gtk_switch_get_active(GTK_SWITCH(widgetOnOffRotacao));
	//Ângulo para rotação do ladrilho
	float angulo = (float) gtk_range_get_value(GTK_RANGE(widgetAnguloLadrilho));
	
	angulo = angulo * (M_PI/180); //Converter para radianos!

	//Pegando a cor do botão
	GdkRGBA rgba;
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(widgetCor), &rgba);

	int y = 0, x = 0;	// Usadas para posição em relação as matrizes das imagens.

	//Armazena a cor do pixel do centro do ladrilho
	int corCh1 = 0, corCh2 = 0, corCh3 = 0;

	int min_i, max_i, min_j, max_j; // Variaveis que guardam a dimensão ocupada pelo ladrilho rotacionando.

	//Armazena o valor selecionado para o tamanho da borda
	int borda = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgetTamanhoBorda));

	//Contador usado na posição aleatória
	int cont = 0;

	//Ajustar nivel no inicio da barra "tamanho do ladrilho". Ex: (na barra)0=2(no sistema), 1=3
	tamLadri+=2;
	
	//Semente para um valor aleatório
	srand(time(NULL));

	//===========================================

	for(i = 0; i < destino.h; i++) { // Preenchendo a matriz da imagem com a cor de fundo.
		for(j = 0; j < destino.w; j++) {
			destino.m[i][j][ch1] = rgba.red*255;
			destino.m[i][j][ch2] = rgba.green*255;
			destino.m[i][j][ch3] = rgba.blue*255;
		}
	}

	//Condições para garantir que o tamanho do ladrilho sempre será no minimo 3 e impar.
	if(tamLadri < 3)
		tamLadri = 3;
	else if(tamLadri%2 == 0)
		tamLadri++;

	// A variável borda é o tamanho da borda do ladrilho.
	for(i = 0; i < destino.h; i = i+tamLadri+borda) { 
		for(j = 0; j < destino.w; j = j+tamLadri+borda) {
	
			//Verifica se o botão da posição aleatória está ativado
			if(gtk_switch_get_active(GTK_SWITCH(widgetOnOffPosLadrilho))){
				//Gera um ponto aleatório
				posicao_aleatoria(destino.h, destino.w, &i, &j);
				
				//Contador determina o máximo de números que serão gerados			
				cont++;
				
				//Verifica se o contador é maior que a área da imagem dividido pela área de cada ladrilho
				if(cont > (destino.h*destino.w)/(tamLadri*tamLadri)){
					return destino;	
				}
			}

			//Pegar a cor do centro do larilho e verifica se não vai pegar um ponto fora dos limites da imagem
			if(i >= 0 && j >= 0 && i < (destino.h - tamLadri/2) && j < (destino.w - tamLadri/2)){
				//O /2 é para pegar a divisão. Então vai pegar o inteiro menor que a metada do tamanho do ladrilho.
				corCh1 = origem.m[i+tamLadri/2][j+tamLadri/2][ch1];
				corCh2 = origem.m[i+tamLadri/2][j+tamLadri/2][ch2];
				corCh3 = origem.m[i+tamLadri/2][j+tamLadri/2][ch3];
			}

			//Verifica se o angulo aleatório está ativado
			if(rot && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widgetRadioAleatorio))){	
				//Sorteia um ângulo aleatório entre 1 e 89
				angulo = 1 + (rand()%88);
				angulo = angulo * (M_PI/180); //Converter para radianos!
			}
			
			//Verifica se o gradiente está ativado
			if(rot && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widgetRadioGradiente))){	
				//Pega o ângulo do ladrilho atrvés do gradiente
				angulo = angulo_gradiente(i+tamLadri/2, j+tamLadri/2, origem);
			}

			/*Condição para saber se o botão de rotação está ativado 
			  Caso rotacionado, definir as novas dimensões do ladrilho. (resolve o problema do ladrilho redondo)*/
            		if(rot){

				//Função para rotacionar ladrilho
				rot_ladrilho(i, j, i, j+tamLadri-1, i+tamLadri-1, j+tamLadri-1, i+tamLadri-1, j, polyX, polyY, i+tamLadri/2, j+tamLadri/2, angulo);

				//Definir as novas dimensões do ladrilho. (resolve o problema do ladrilho redondo)
				min_max(polyX, polyY, &min_i, &max_i, &min_j, &max_j);

				for(y = min_i; y < max_i; y++) {
					for(x = min_j; x < max_j; x++) {
					
						/*Condição para saber se o ponto está dentro do ladrilho rotacionado
						  Caso verdadeiro, pinta o pixel*/
						if(pointInPolygon(4, y, x) == 1 && y < destino.h && x < destino.w && y >= 0 && x >= 0){
							destino.m[y][x][0] = corCh1;
							destino.m[y][x][1] = corCh2;
							destino.m[y][x][2] = corCh3;
						}
					}
				}

            		}else{
				//Caso não rotacionado, pinta os pixels normalmente
				for(y = i; y < i+tamLadri; y++) {
					for(x = j; x < j+tamLadri; x++) {
						if(y < destino.h && x < destino.w){
							destino.m[y][x][0] = corCh1;
							destino.m[y][x][1] = corCh2;
							destino.m[y][x][2] = corCh3;
						}
					}
				}
            		}
		}
	}

	return destino;
}

//===================================== Funções ==================================================
// Faz a rotação de um ponto do vértice do ladrilho em relação ao ângulo.
void rotacaoPonto(int *Vx, int *Vy, float Cx, float Cy, float t){ // t = teta
	
	float Ax, Ay; //Variaveis auxiliares;

	float sent = sin(t), cost = cos(t); //Calculo os seno e cosseno do ângulo.

	//Armazena os valores dos vértices
	float Bx = *Vx, By = *Vy;

	//Transfere o vértice para o centro do plano cartesiano
	Bx = Bx - Cx;
	By = By - Cy;

	//Rotaciona o ponto
	Ax = cost*Bx - sent*By;
	Ay = sent*Bx + cost*By;
	
	//O ponto sai do centro do plano e vai para a nova posição rotacionada
	Ax = Ax + Cx;
	Ay = Ay + Cy;

	//Arredonda para o inteiro mais próximo. obs: permanece em float
	Ax = round(Ax);
	Ay = round(Ay);

	//Transforma para interio
	*Vx = (int) Ax;
	*Vy = (int) Ay;
}

//================================================================================================

//Função que determina se o ponto está dentro ou fora de um polígono
//Retirado de: http://alienryderflex.com/polygon/
int pointInPolygon(int polyCorners, int x, int y) {

  int  i, j=polyCorners-1;
  int  oddNodes = 0;

	  for (i=0; i<polyCorners; i++) {
    if ((polyY[i]< y && polyY[j]>=y    ||   polyY[j]< y && polyY[i]>=y)    &&  (polyX[i]<=x || polyX[j]<=x)) {
      if (polyX[i]+(y-polyY[i])/(polyY[j]-polyY[i])*(polyX[j]-polyX[i])<x) {
        oddNodes=!oddNodes; }}
    j=i; }

  return oddNodes;
}

//================================================================================================

/*Função para rotacionar todos os pontos dos vértices do ladrilho. Recebe os quatro pontos, 
os vetores usados na função que verifica se o ponto está dentro, e ângulo de rotação. 
Chama a função que rotacionada um ponto, para cada vertice passado.*/
void rot_ladrilho(int P1x, int P1y, int P2x, int P2y, int P3x, int P3y, int P4x, int P4y, float *polyX_1, float *polyY_1, int PCx, int PCy, float ang){
	rotacaoPonto(&P1x, &P1y, PCx, PCy, ang);
	polyX_1[0] = P1x;
	polyY_1[0] = P1y;

	rotacaoPonto(&P2x, &P2y, PCx, PCy, ang);
	polyX_1[1] = P2x;
	polyY_1[1] = P2y;

	rotacaoPonto(&P3x, &P3y, PCx, PCy, ang);
	polyX_1[2] = P3x;
	polyY_1[2] = P3y;

	rotacaoPonto(&P4x, &P4y, PCx, PCy, ang);
	polyX_1[3] = P4x;
	polyY_1[3] = P4y;
}

//================================================================================================

//Função para pegar os valores maximos e minimos do ladrilho rotacionando.
void min_max(float *polyX_2, float *polyY_2, int *min_i, int *max_i, int *min_j, int *max_j){
	//Inicia os valores das variáveis
	*min_i = (int) polyX[0];
	*max_i = (int) polyX[0];
	*min_j = (int) polyX[0];
	*max_j = (int) polyX[0];

	//Percorre o vetor e verifica os máximos e mínimos dos pontos
	for( int k = 0; k < 4; k++){
		if(polyX[k] < *min_i)
			*min_i = (int) polyX[k];
		if(polyX[k] > *max_i)
			*max_i = (int) polyX[k];
		if(polyY[k] < *min_j)
			*min_j = (int) polyY[k];
		if(polyY[k] > *max_j)
			*max_j = (int) polyY[k];
	}
}

//================================================================================================
//Calculo o ângulo do vetor gradiente da região central do ladrilho.
float angulo_gradiente(int gy, int gx, Imagem imagem){

	//gx e gy = centro do ladrilho
	
	int filtrox[3][3] = {-1,0,1,-2,0,2,-1,0,1}; //Filtro de Sobel
	int filtroy[3][3] = {-1,-2,-1,0, 0,0,1,2,1}; //Filtro de Sobel

	//int filtrox[3][3] = {-1,0,1,-1,0,1,-1,0,1}; //Filtro de Prewitt
	//int filtroy[3][3] = {-1,-1,-1,0, 0,0,1,1,1}; //Filtro de Prewitt


	//Gradiente x e y
	float dx = 0, dy = 0;
	
	//Desloca o valor que era do centro, para um pixel acima. Passando a ser o canto superior esquerdo do ladrilho
	gy--;
	gx--;

	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){

			//Aplica o cálculo do filtro
			if(((gy+i) >= 0) && ((gx+j) >= 0) && ((gy+i) < imagem.h) && ((gx+j) < imagem.w) ){
				dy += filtroy[i][j] * imagem.m[gy+i][gx+j][0];
				dx += filtrox[i][j] * imagem.m[gy+i][gx+j][0];
			}
		}
	}

	//atan2 pega o ângulo do gradiente
	return atan2(dy, dx);
}

//================================================================================================

void posicao_aleatoria(int tamanhoI, int tamanhoJ, int *novoI, int *novoJ){

	*novoI = rand()%(tamanhoI-1);
	*novoJ = rand()%(tamanhoJ-1);
}

//================================================================================================

//Ativa ou desativa os widgets quando necessário!
void ativaWidgets(){

	//Verifica se o botão de rotação está ativado
	if(gtk_switch_get_active(GTK_SWITCH(widgetOnOffRotacao))){
		gtk_widget_set_sensitive(widgetRadioGradiente, TRUE);
		gtk_widget_set_sensitive(widgetRadioAleatorio, TRUE);
		gtk_widget_set_sensitive(widgetRadioFixo, TRUE);
	
	} else {
		gtk_widget_set_sensitive(widgetRadioGradiente, FALSE);
		gtk_widget_set_sensitive(widgetRadioAleatorio, FALSE);
		gtk_widget_set_sensitive(widgetRadioFixo, FALSE);
		gtk_widget_set_sensitive(widgetAnguloLadrilho, FALSE);
	}

	//Verifica se o botão de rotação está ativado e o radio button aleatório ou o radio button gradiente está ativado
	if(gtk_switch_get_active(GTK_SWITCH(widgetOnOffRotacao)) && (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widgetRadioAleatorio))	||	gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widgetRadioGradiente)))){
		gtk_widget_set_sensitive(widgetAnguloLadrilho, FALSE);
	} else if(gtk_switch_get_active(GTK_SWITCH(widgetOnOffRotacao)) && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widgetRadioFixo))) {
		gtk_widget_set_sensitive(widgetAnguloLadrilho, TRUE);
	}

}

