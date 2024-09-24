typedef enum {
    IDLE = 0,
    CONNECTED = 1,
    INACTIVE = 2
}STATE;

struct connected_ue {
    int id;
    STATE state;
}; 

