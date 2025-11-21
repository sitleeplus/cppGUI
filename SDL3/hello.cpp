#include "SDL3/SDL.h"
#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <iostream>
#include <string>
#define U8(x) reinterpret_cast<const char*>(x)

class TESTG {
public:
    TESTG() : window(nullptr), renderer(nullptr), font(nullptr), running(false) {}

    bool Init() {
        const int window_w = 640;
        const int window_h = 480;
        
        int ret = SDL_Init(SDL_INIT_VIDEO);
        if (ret < 0) {
            SDL_Log("SDL_Init() Error: %s", SDL_GetError());
            return -1;
        }
        ret = TTF_Init();
        if (ret < 0) {
            std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        window = SDL_CreateWindow("SDL3 TTF Sample", window_w, window_h, SDL_WINDOW_RESIZABLE);
        if (!window) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            return false;
        }

        renderer = SDL_CreateRenderer(window, nullptr);
        if (!renderer) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            return false;
        }

        font = TTF_OpenFont("C:/Windows/Fonts/meiryo.ttc", 32);
        if (!font) {
            std::cerr << "TTF_OpenFont Error: " << SDL_GetError() << std::endl;
            return false;
        }

        running = true;
        return true;
    }

    void Run() {
        while (running) {
            HandleEvents();
            Update();
            Render();
        }
    }

    ~TESTG() {
        if (font) TTF_CloseFont(font);
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
    }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    bool running;

    void HandleEvents() {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
    }

    void Update() {
        // 今回は特に更新処理なし
    }

    void Render() {
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        // UTF-8文字列を描画
        const char8_t* text8 = u8"こんにちは SDL3 + TTF!";
        size_t len = std::char_traits<char8_t>::length(text8);

        SDL_Surface* surface = TTF_RenderText_Blended(font, U8(text8), std::strlen(U8(text8)), SDL_Color{ 255, 255, 255, 255 });
        if (surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FRect dstRect{ 50.0f, 50.0f, (float)surface->w, (float)surface->h };
            SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
            SDL_DestroyTexture(texture);
            SDL_DestroySurface(surface);
        }

        SDL_RenderPresent(renderer);
    }
};

int main(int argc, char** argv) {
    TESTG testg;
    if (!testg.Init()) {
        return -1;
    }
    testg.Run();
    return 0;
}
