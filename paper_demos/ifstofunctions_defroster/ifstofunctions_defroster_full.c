typedef void ErrorType ;
typedef void Void ;
typedef signed char Int8 ;
typedef unsigned char UInt8 ;
typedef signed short Int16 ;
typedef unsigned int UInt16 ;
typedef signed int Int32 ;
typedef unsigned int UInt32 ;

typedef struct {
    unsigned int We7_BE_LOSGELASSEN : 1;
    unsigned int We6_BE_CONFIRM_ON : 1;
    unsigned int We12_BLINK_ON : 1;
    unsigned int We9_DEF_OUT : 1;
    unsigned int We8_BE_CONFIRM_OUT : 1;
    unsigned int We5_BE_HANDLING : 1;
    unsigned int We11_BLINK_OUT : 1;
    unsigned int We2_Clip15_OUT : 1;
    unsigned int We3_Clip15_ON : 1;
} AU8_tp ;


typedef UInt8 Bool ;

unsigned  char error_e = nondet_uchar();
unsigned  char confirmation_e = nondet_uchar();
unsigned  char Clip_15 = nondet_uchar();
unsigned  char ControlElement_DEF = nondet_uchar();
unsigned  char control_led = nondet_uchar();
unsigned  char request = nondet_uchar();
AU8_tp AU8 ;

signed short We1_BA_DEF_ev_ctr0 = nondet_short();
signed short We1_BA_DEF_ev_ctr1 = nondet_short();
signed short We1_BA_DEF_ev_ctr2 = nondet_short();
signed short We1_BA_DEF_ev_ctr3 = nondet_short();
signed short We1_BA_DEF_ev_ctr5 = nondet_short();

signed short We1_BA_DEF_ev = nondet_short();
signed short We1_BA_DEF ;

void Exception_handler ( void ) {
    
    if ( AU8.We6_BE_CONFIRM_ON ) {
        if_line_42();
    }
    else {
        else_line_45();
    }
}
void if_line_42() {
    AU8.We6_BE_CONFIRM_ON = nondet_int();
}
void else_line_45() {
    if ( AU8.We7_BE_LOSGELASSEN ) {
        if_line_46();
    }
}
void if_line_46() {
    AU8.We7_BE_LOSGELASSEN = nondet_int();
}
void if_line_73() {
    AU8.We11_BLINK_OUT = nondet_int();
}
void if_line_72() {
    if ( AU8.We11_BLINK_OUT ) {
        if_line_73();
    }
    else {
        else_line_76();
    }
    if ( AU8.We5_BE_HANDLING ) {
        if_line_81();
    }
    else {
        else_line_84();
    }
    AU8.We3_Clip15_ON = nondet_int();
    request = nondet_uchar();
    control_led = nondet_uchar();
    AU8.We2_Clip15_OUT = nondet_int();
}
void if_line_71() {
    if ( Clip_15 == 0) {
        if_line_72();
    }
    else {
        else_line_99();
    }
}

void if_line_148() {
    AU8.We11_BLINK_OUT = nondet_int();
}
void if_line_115() {
    Exception_handler ();
    request = nondet_uchar();
    AU8.We8_BE_CONFIRM_OUT = nondet_int();
}
void if_line_114() {
    if ( ControlElement_DEF > 0) {
        if_line_115();
    }
}
void if_line_144() {
    AU8.We11_BLINK_OUT = nondet_int();
}
void if_line_175() {
    We1_BA_DEF_ev_ctr2 = nondet_short();
}
void if_line_143() {
    if (( We1_BA_DEF_ev_ctr0 >= (( signed short ) 3250 )) && error_e > 0 && confirmation_e > 0) {
        if_line_144();
    }
    else {
        else_line_147();
    }
}
void if_line_171() {
    We1_BA_DEF_ev_ctr2 = nondet_short();
}
void else_line_76() {
    if ( AU8.We12_BLINK_ON ) {
        if_line_77();
    }
}
void else_line_147() {
    if ( request > 0 && ( error_e == 0)) {
        if_line_148();
    }
}
void else_line_178() {
    We1_BA_DEF_ev_ctr2 = nondet_short();
}
void else_line_113() {
    if ( AU8.We7_BE_LOSGELASSEN ) {
        if_line_114();
    }
}
void if_line_68() {
    We1_BA_DEF_ev_ctr2 = nondet_short();
}
void else_line_174() {
    if (( We1_BA_DEF_ev_ctr2 ) - ( We1_BA_DEF_ev_ctr3 ) - ( We1_BA_DEF_ev_ctr5 ) == 1024)  {
        if_line_175();
    }
    else {
        else_line_178();
    }
}
void if_line_108() {
    AU8.We6_BE_CONFIRM_ON = nondet_int();
    AU8.We7_BE_LOSGELASSEN = nondet_int();
}
void if_line_107() {
    if ( ControlElement_DEF == 0) {
        if_line_108();
    }
}
void if_line_101() {
    Exception_handler ();
    request = nondet_uchar();
    AU8.We9_DEF_OUT = nondet_int();
}
void if_line_133() {
    AU8.We9_DEF_OUT = nondet_int();
    request = nondet_uchar();
    We1_BA_DEF_ev_ctr1 = nondet_short();
    AU8.We5_BE_HANDLING = nondet_int();
    AU8.We6_BE_CONFIRM_ON = nondet_int();
}
void if_line_100() {
    if (( We1_BA_DEF_ev_ctr1 >= (( signed short ) 1000 )) && ( confirmation_e == 0 ) && ( ControlElement_DEF == 0 )) {
        if_line_101();
    }
    else {
        else_line_106();
    }
}
void if_line_132() {
    if ( ControlElement_DEF > 0) {
        if_line_133();
    }
}
void else_line_99() {
    if ( AU8.We5_BE_HANDLING ) {
        if_line_100();
    }
    else {
        else_line_124();
    }
    if ( AU8.We11_BLINK_OUT ) {
        if_line_143();
    }
    else {
        else_line_153();
    }
}
void else_line_66() {
    We1_BA_DEF = We1_BA_DEF_ev_ctr2 * We1_BA_DEF_ev_ctr2 - ( We1_BA_DEF_ev_ctr3 - 1000);   //mutated statement
    if ( ! ( We1_BA_DEF == We1_BA_DEF_ev )) {
        if_line_68();
    }
    if ( AU8.We3_Clip15_ON ) {
        if_line_71();
    }
    else {
        else_line_167();
    }
}
void else_line_106() {
    if ( AU8.We6_BE_CONFIRM_ON ) {
        if_line_107();
    }
    else {
        else_line_113();
    }
}
void else_line_167() {
    AU8.We2_Clip15_OUT = nondet_int();
}
void if_line_57() {
    AU8.We2_Clip15_OUT = nondet_int();
    AU8.We3_Clip15_ON = nondet_int();
    AU8.We9_DEF_OUT = nondet_int();
    We1_BA_DEF_ev_ctr0 = nondet_short();
    AU8.We11_BLINK_OUT = nondet_int();
    control_led = nondet_uchar();
}
void if_line_89() {
    AU8.We9_DEF_OUT = nondet_int();
}
void if_line_56() {
    if ( Clip_15 ) {
        if_line_57();
    }
}
void else_line_131() {
    if ( AU8.We9_DEF_OUT ) {
        if_line_132();
    }
}
void if_line_85() {
    AU8.We8_BE_CONFIRM_OUT = nondet_int();
}
void if_line_81() {
    Exception_handler ();
}
void if_line_159() {
    AU8.We12_BLINK_ON = nondet_int();
}
void if_line_126() {
    AU8.We8_BE_CONFIRM_OUT = nondet_int();
    AU8.We9_DEF_OUT = nondet_int();
}
void if_line_125() {
    if ( ControlElement_DEF == 0) {
        if_line_126();
    }
}
void if_line_155() {
    AU8.We12_BLINK_ON = nondet_int();
}
void if_line_154() {
    if (( request == 0) && ( error_e == 0)) {
        if_line_155();
    }
    else {
        else_line_158();
    }
}
void else_line_88() {
    if ( AU8.We9_DEF_OUT ) {
        if_line_89();
    }
}
void else_line_158() {
    if (( We1_BA_DEF_ev_ctr0 >= (( signed short ) 3250 )) && error_e > 0 && confirmation_e > 0) {
        if_line_159();
    }
}
void else_line_84() {
    if ( AU8.We8_BE_CONFIRM_OUT ) {
        if_line_85();
    }
    else {
        else_line_88();
    }
}
void else_line_124() {
    if ( AU8.We8_BE_CONFIRM_OUT ) {
        if_line_125();
    }
    else {
        else_line_131();
    }
}
void if_line_77() {
    AU8.We12_BLINK_ON = nondet_int();
}
void else_line_153() {
    if ( AU8.We12_BLINK_ON ) {
        if_line_154();
    }
}

main () {
    
    AU8.We7_BE_LOSGELASSEN = nondet_int();
    AU8.We6_BE_CONFIRM_ON = nondet_int();
    AU8.We12_BLINK_ON = nondet_int();
    AU8.We9_DEF_OUT = nondet_int();
    AU8.We8_BE_CONFIRM_OUT = nondet_int();
    AU8.We5_BE_HANDLING = nondet_int();
    AU8.We11_BLINK_OUT = nondet_int();
    AU8.We2_Clip15_OUT = nondet_int();
    AU8.We3_Clip15_ON = nondet_int();
    
    We1_BA_DEF_ev_ctr1 ++ ;
    We1_BA_DEF_ev_ctr0 ++ ;
    if ( AU8.We2_Clip15_OUT ) {
        if_line_56();
    }
    else {
        else_line_66();
    }
    if ( We1_BA_DEF_ev_ctr2 + We1_BA_DEF_ev_ctr3 + We1_BA_DEF_ev_ctr5 == 1024)  {
        //if_line_171();
    }
    else {
        //else_line_174();
    }
    
    _Learn_assert(1 == 0);
}