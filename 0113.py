import pygame
import random

# 初始化 pygame
pygame.init()

# 視窗設定
WIDTH, HEIGHT = 600, 400
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("接住掉落物遊戲")

# 顏色定義
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
BLUE = (0, 0, 255)

# 遊戲物件參數
player_width, player_height = 50, 10
player_x = WIDTH // 2 - player_width // 2
player_y = HEIGHT - 30
player_speed = 5

object_width, object_height = 20, 20
object_x = random.randint(0, WIDTH - object_width)
object_y = 0
object_speed = 3

# 分數
score = 0
font = pygame.font.Font(None, 36)

# 遊戲時鐘
clock = pygame.time.Clock()
running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # 玩家控制
    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT] and player_x > 0:
        player_x -= player_speed
    if keys[pygame.K_RIGHT] and player_x < WIDTH - player_width:
        player_x += player_speed

    # 更新掉落物位置
    object_y += object_speed

    # 檢查是否接住
    if (player_x < object_x < player_x + player_width or player_x < object_x + object_width < player_x + player_width) and \
            player_y < object_y + object_height < player_y + player_height:
        score += 1
        object_x = random.randint(0, WIDTH - object_width)
        object_y = 0
        object_speed += 0.2  # 增加難度

    # 檢查是否掉出螢幕
    if object_y > HEIGHT:
        object_x = random.randint(0, WIDTH - object_width)
        object_y = 0

    # 畫面更新
    screen.fill(WHITE)

    # 畫玩家
    pygame.draw.rect(screen, BLUE, (player_x, player_y, player_width, player_height))

    # 畫掉落物
    pygame.draw.rect(screen, RED, (object_x, object_y, object_width, object_height))

    # 顯示分數
    score_text = font.render(f"Score: {score}", True, BLACK)
    screen.blit(score_text, (10, 10))

    # 更新畫面
    pygame.display.flip()

    # 控制遊戲速度
    clock.tick(60)

pygame.quit()
