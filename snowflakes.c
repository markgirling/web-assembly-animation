#define VIEW_WIDTH 400
#define VIEW_HEIGHT 400
#define PIXEL_SIZE 2
#define NUM_SNOWFLAKES 100

// This external functions are defined at runtime in JS
extern void fill_canvas(char *colour, int x, int y, int w, int h);
extern int rand_num(int max);

struct snowflake {
  int x;
  int y;
  int speed;
};

struct snowflake snowflakes[NUM_SNOWFLAKES];

void init_snowflakes() {
  for(int i = 0; i < NUM_SNOWFLAKES; i++) {
    struct snowflake sflake;
    sflake.x = PIXEL_SIZE * (rand_num((VIEW_WIDTH / PIXEL_SIZE)));
    sflake.y = PIXEL_SIZE * (rand_num((VIEW_HEIGHT / PIXEL_SIZE)));
    sflake.speed = rand_num(2) + 1;
    snowflakes[i] = sflake;
  }
}

void fill_bg() {
  fill_canvas("#2196f3", 0, 0, VIEW_WIDTH, VIEW_HEIGHT / 3);
  fill_canvas("#1e88e5", 0, VIEW_HEIGHT / 3, VIEW_WIDTH, VIEW_HEIGHT / 3);
  fill_canvas("#1976d2", 0, (VIEW_HEIGHT / 3) * 2, VIEW_WIDTH, VIEW_HEIGHT / 3);
}

void render_snowflake(struct snowflake *sflake) {
  int x = sflake->x;
  int y = sflake->y;

  for(int i = 0; i <= 6; i++) {
    fill_canvas("#ffffff", x + PIXEL_SIZE * i, y + PIXEL_SIZE * i, PIXEL_SIZE, PIXEL_SIZE);
    fill_canvas("#ffffff", x + PIXEL_SIZE * i, y + PIXEL_SIZE * (6 - i), PIXEL_SIZE, PIXEL_SIZE);
    fill_canvas("#ffffff", x + PIXEL_SIZE * 3, y + PIXEL_SIZE * i, PIXEL_SIZE, PIXEL_SIZE);
    fill_canvas("#ffffff", x + PIXEL_SIZE * i, y + PIXEL_SIZE * 3, PIXEL_SIZE, PIXEL_SIZE);
  }
}

void move_snowflake(struct snowflake *sflake) {
  sflake->y = sflake->y + sflake->speed;
  if(sflake->y > VIEW_HEIGHT) {
    sflake->y = -(PIXEL_SIZE * 7);
  }
}

void render_snowflakes() {
  fill_bg();

  for(int i = 0; i < NUM_SNOWFLAKES; i++) {
    move_snowflake(&snowflakes[i]);
    render_snowflake(&snowflakes[i]);
  }
}
