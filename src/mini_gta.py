import pygame
import sys

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
WORLD_WIDTH = 2000
WORLD_HEIGHT = 2000
PLAYER_SIZE = 40
PLAYER_COLOR = (0, 255, 0)
BACKGROUND_COLOR = (50, 50, 50)

class Player:
    def __init__(self):
        self.rect = pygame.Rect(WORLD_WIDTH // 2, WORLD_HEIGHT // 2, PLAYER_SIZE, PLAYER_SIZE)
        self.speed = 5

    def handle_input(self, keys):
        if keys[pygame.K_w] or keys[pygame.K_UP]:
            self.rect.y -= self.speed
        if keys[pygame.K_s] or keys[pygame.K_DOWN]:
            self.rect.y += self.speed
        if keys[pygame.K_a] or keys[pygame.K_LEFT]:
            self.rect.x -= self.speed
        if keys[pygame.K_d] or keys[pygame.K_RIGHT]:
            self.rect.x += self.speed

    def draw(self, surface, camera):
        draw_rect = self.rect.move(-camera.x, -camera.y)
        pygame.draw.rect(surface, PLAYER_COLOR, draw_rect)

def main():
    pygame.init()
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    clock = pygame.time.Clock()
    player = Player()
    camera = pygame.Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        keys = pygame.key.get_pressed()
        player.handle_input(keys)

        camera.center = player.rect.center
        camera.clamp_ip(pygame.Rect(0, 0, WORLD_WIDTH, WORLD_HEIGHT))

        screen.fill(BACKGROUND_COLOR)
        player.draw(screen, camera)
        pygame.display.flip()
        clock.tick(60)

    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    main()
