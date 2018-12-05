#ifndef MEUFILTRO_H
#define MEUFILTRO_H

#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>
#include <time.h>
#include "imagem.h"
#include <math.h>

//declare aqui os seus widgets
GtkWidget *widgetTituloTamLadrilho;
GtkWidget *widgetTamanhoLadrilho;
GtkWidget *widgetTituloAnguLadrilho;
GtkWidget *widgetAnguloLadrilho;
GtkWidget *widgetSeparador;
GtkWidget *widgetTituloOrientacaoLadrilho;
GtkWidget *widgetRadio;
GtkWidget *widgetRadioAleatorio;
GtkWidget *widgetRadioGradiente;
GtkWidget *widgetRadioFixo;
GtkWidget *widgetCor;
GtkWidget *widgetOnOffRotacao;
GtkWidget *widgetOnOffPosLadrilho;
GtkWidget *widgetTituloPosAleatoriaLadrilho;
GtkWidget *widgetTituloCorFundo;
GtkWidget *widgetTituloTamanhoBorda;
GtkWidget *widgetTamanhoBorda;

Imagem meuFiltro(Imagem origem);
void inicializarWidgetsMeuFiltro();
void adicionarWidgetsMeuFiltro(GtkWidget *container);

//esta funcao esta implementada em filtroGtk.c, nao precisa alterar
void funcaoAplicar(GtkWidget *widget, gpointer data);

float  polyX[4];
float  polyY[4];

void rotacaoPonto(int *Vx, int *Vy, float Cx, float Cy, float t);

int pointInPolygon(int polyCorners, int x, int y);

void rot_ladrilho(int P1x, int P1y, int P2x, int P2y, int P3x, int P3y, int P4x, int P4y, float *polyX_1, float *polyY_1, int PCx, int PCy, float ang);

void min_max(float *polyX_2, float *polyY_2, int *min_i, int *max_i, int *min_j, int *max_j);

float angulo_gradiente(int gy, int gx, Imagem imagem);

void posicao_aleatoria(int tamanhoI, int tamanhoJ, int *novoI, int *novoJ);

void ativaWidgets();

#endif


