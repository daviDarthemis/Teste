#pragma once

// Incluímos o nosso próprio tipo de vetor4 para cores.
// Por agora, será uma estrutura simples.
struct Vector4 {
    unsigned char r, g, b, a;
};

// Forward declaration para não incluir SDL no cabeçalho.
struct SDL_Window;
struct SDL_Renderer;

class Renderer {
public:
    Renderer();
    ~Renderer();

    // Inicializa o subsistema de renderização. Precisa da janela para se associar.
    // Retorna 'true' em caso de sucesso, 'false' em caso de falha.
    bool Init(SDL_Window* window);

    // Liberta todos os recursos de renderização.
    void Shutdown();

    // Prepara o início de um novo frame, limpando o ecrã com uma cor.
    void BeginFrame();

    // Apresenta o frame desenhado no ecrã.
    void EndFrame();

    // A nossa primeira primitiva de desenho. Desenha um pixel.
    void DrawPixel(int x, int y, const Vector4& color);

private:
    // O ponteiro para o renderizador do SDL. Agora é responsabilidade desta classe.
    SDL_Renderer* m_SdlRenderer;
};
