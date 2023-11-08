
struct _PacmanNamespace {
    void (*Initialize)();
    void (*Update)();
    void (*Finalize)();
};
extern struct _PacmanNamespace Pacman;



