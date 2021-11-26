#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Player {
    char *name;
    int hp; // health points
    int ad; // attack damage
    int dp; // defense points
    int luck; // luck factor for fatal hit out of 100
} Player;

void generate_player(Player *player) {
    player->name = "Player\0";
    player->hp = 100;
    player->ad = 100;
    player->dp = 20;
    player->luck = 10;
}

void generate_opponent(Player *player) {
    player->name = "Opponent\0";
    player->hp = 100;
    player->ad = rand()%90;
    player->dp = rand()%15;
    player->luck = 1;
}

int is_lucky_strike(int luck) {
    if (rand()%100 < luck) return 1;
    return 0;
}

void attack(Player *attacker, Player *defender) {
    if (is_lucky_strike(attacker->luck) == 1) {
        printf("**%s launches CRITICAL HIT on %s**\n",attacker->name,defender->name);
        defender->hp = 0;
    } else {
        int damage = attacker->ad - defender->dp;
        if (damage < 0) damage = 0;
        printf("%s attacks %s for %d\n",attacker->name,defender->name,damage);
        defender->hp -= damage;
    }
}

void print_stat(Player *player) {
    printf("HP: %d\tAD: %d\tDP: %d\tLuck: %d\n",player->hp,player->ad,player->dp,player->luck);
}

void print_hp(Player *player) {
    printf("HP: %d\n", player->hp);
}

void wait_for_user() {
    printf("Press the ENTER key to continue...");  
    getchar();
}

void lose_screen() {
    printf("You have passed out.\n");
    printf("The arbiter takes advantage of your unconscious self and slits your throat. Hey, at least it was painless.\n");
    wait_for_user();
    exit(0);
}

void introduce() {
    printf(
        "Welcome to the Impossible Brawl!\n"
        "The goal of this game is to take turns slapping each other in the face. The last side standing wins!\n"
        "\n"
        "Your scenario:\n"
        "You shamelessly bragged about your 10 gold medals from your martial art competitions, and the arbiter now hates you. The arbiter decided you to invite you to his Impossible Brawl martial competition to \"prove\" your prowess. Because of your ginormous ego, you couldn't turn down the offer and signed up. The rules of the game only require that each contestant take turns; there was no talk on how many contestants could be on each side. However, the arbiter conveniently neglected to tell you a small detail: you would be facing against 10 other martial artists. You fall unconcious if your health reaches 0, and the same applies for them.\n\n"
    );
}

int main() {
    time_t t;
    srand((unsigned) time(&t));
    introduce();
    Player me;
    generate_player(&me);
    printf("You: ");
    print_stat(&me);
    for (int i=1; i<=10; i++) {
        Player opponent;
        generate_opponent(&opponent);
        printf("Op%i: ",i);
        print_stat(&opponent);
        wait_for_user();
        int turn_flag = 0; // 0 is player, 1 is opponent
        while (1) {
            if (turn_flag == 0) {
                turn_flag = 1;
                attack(&me, &opponent);
            } else {
                turn_flag = 0;
                attack(&opponent, &me);
            }
            printf("You: ");
            print_hp(&me);
            printf("Op%d: ", i);
            print_hp(&opponent);
            if (opponent.hp <= 0) {
                printf("Opponent %d has passed out.\n", i);
                printf("============================\n");
                printf("You: ");
                print_stat(&me);
                break;
            }
            if (me.hp <= 0) {
                lose_screen();
            }
        }
    }
    printf("The arbiter is shocked to witness you knocking down the ten expert martial artists. He now praises you as the \"Chosen One.\"\n");
    wait_for_user();
    return 0;
}
