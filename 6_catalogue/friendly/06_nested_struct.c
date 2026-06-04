/* structures imbriquees : EVA suit les champs precisement */

struct point { int x; int y; };
struct line { struct point a; struct point b; };

int main(void) {
    struct line l = { {1, 2}, {3, 4} };
    int dx = l.b.x - l.a.x;
    int dy = l.b.y - l.a.y;
    /*@ assert dx == 2; */
    /*@ assert dy == 2; */
    return dx + dy;
}
