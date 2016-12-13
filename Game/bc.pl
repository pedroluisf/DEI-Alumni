%------------------------------------------------------------------------------------
% kick-off p/LAPR5 e ALGAV
%------------------------------------------------------------------------------------
:-dynamic nodo/4,ramo/4.
:-dynamic restricao/6,ponto_entrega/2,camiao/5,encomenda/3,relogio/2.
%------------------------------------------------------------------------------------
% Caracterização grafo
%------------------------------------------------------------------------------------
%-----------------------------------------------------------
% nodo(IdNodo,PosX,PosY)
%-----------------------------------------------------------
nodo(a,-10,-10,0).
nodo(b,0,-10,0).
nodo(c,10,-10,0).
nodo(d,-10,0,0).
nodo(e,0,0,5).
nodo(f,10,0,0).
nodo(g,-10,10,0).
nodo(h,0,10,0).
nodo(i,10,10,0).
%-----------------------------------------------------------
% ramo(IdRamo,IdNodo1,IdNodo2,Distancia)
%-----------------------------------------------------------
ramo(r1,a,b,10).
ramo(r2,a,d,10).
ramo(r3,b,c,10).
ramo(r4,b,e,11.1803).
ramo(r5,c,f,10).
ramo(r6,d,e,11.1803).
ramo(r7,d,h,14.1421).
ramo(r8,e,f,11.1803).
ramo(r9,e,h,11.1803).
ramo(r10,f,i,10).
ramo(r11,g,h,10).
ramo(r12,h,i,10).
%-----------------------------------------------------------
% restricao(IdRamo,InicoOuFim,Tipo,Valor,Hora,Minuto)
%
% Tipo: velocidade, largura, altura, explosivo, inflamavel, peso, ...
%-----------------------------------------------------------
restricao(r1,inicio,velocidade,20,8,30).
restricao(r5,inicio,inflamavel,_,0,0).
restricao(r4,inicio,explosivo,_,8,0).
restricao(r1,fim,velocidade,_,22,0).
restricao(r7,inicio,velocidade,45,11,30).
restricao(r3,inicio,altura,4,0,0).
restricao(r3,inicio,peso,3000,0,0).
%------------------------------------------------------------------------
% ponto_entrega(IdPontoEntrega,IdNodo)
% - IdNodo: define qual o nodo do grafo em que se localiza a ponto_entrega
%------------------------------------------------------------------------
ponto_entrega(aveiro,c).
ponto_entrega(faro,d).
ponto_entrega(chaves,f).
%-----------------------------------------------------------------------------
% camiao(Matricula,NoInicio,Peso,Largura, Altura,VelocidadeMax)
%-----------------------------------------------------------------------------
camiao('xx-20-20', a,3500, 2.2, 1.85, 80).
%------------------------------------------------------------------------
% encomenda(IdEmissor,Tipo,PontoEntrega)
%------------------------------------------------------------------------
encomenda(e101,[inflamavel,explosivo],faro).
encomenda(e102,[],aveiro).
encomenda(e103,[],faro).
encomenda(e104,[],chaves).
encomenda(e105,[],chaves).
encomenda(e106,[],faro).
encomenda(e107,[],aveiro).
%------------------------------------------------------------------------
% relogio(Hora,Minuto)
%------------------------------------------------------------------------
relogio(9,40).
