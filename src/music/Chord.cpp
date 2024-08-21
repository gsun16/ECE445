#include "Chord.h"

Chord::Chord(char id, String name, std::vector<Note*> notes)
    : Sound(Sound::Type::CHORD, id, name), notes(notes) {}

// Major Chords
Chord Chord::C  = Chord(150, "C",  {&Note::C_4,  &Note::E_4,  &Note::G_4});
Chord Chord::Db = Chord(151, "Db", {&Note::Db_4, &Note::F_4,  &Note::Ab_4});
Chord Chord::D  = Chord(152, "D",  {&Note::D_4,  &Note::F_4,  &Note::A_4});
Chord Chord::Eb = Chord(153, "Eb", {&Note::Eb_4, &Note::G_4,  &Note::Bb_4});
Chord Chord::E  = Chord(154, "E",  {&Note::E_4,  &Note::G_4,  &Note::B_4});
Chord Chord::F  = Chord(155, "F",  {&Note::F_4,  &Note::A_4,  &Note::C_5});
Chord Chord::Gb = Chord(156, "Gb", {&Note::Gb_4, &Note::Bb_4, &Note::Db_5});
Chord Chord::G  = Chord(157, "G",  {&Note::G_4,  &Note::B_4,  &Note::D_5});
Chord Chord::Ab = Chord(158, "Ab", {&Note::Ab_4, &Note::C_5,  &Note::Eb_5});
Chord Chord::A  = Chord(159, "A",  {&Note::A_4,  &Note::C_5,  &Note::E_5});
Chord Chord::Bb = Chord(160, "Bb", {&Note::Bb_4, &Note::D_5,  &Note::F_5});
Chord Chord::B  = Chord(161, "B",  {&Note::B_4,  &Note::D_5,  &Note::F_5});

// Minor Chords
Chord Chord::Cm  = Chord(162, "Cm",  {&Note::C_4,  &Note::Eb_4, &Note::G_4});
Chord Chord::Dbm = Chord(163, "Dbm", {&Note::Db_4, &Note::E_4,  &Note::Ab_4});
Chord Chord::Dm  = Chord(164, "Dm",  {&Note::D_4,  &Note::F_4,  &Note::A_4});
Chord Chord::Ebm = Chord(165, "Ebm", {&Note::Eb_4, &Note::Gb_4, &Note::Bb_4});
Chord Chord::Em  = Chord(166, "Em",  {&Note::E_4,  &Note::G_4,  &Note::B_4});
Chord Chord::Fm  = Chord(167, "Fm",  {&Note::F_4,  &Note::Ab_4, &Note::C_5});
Chord Chord::Gbm = Chord(168, "Gbm", {&Note::Gb_4, &Note::A_4,  &Note::Db_5});
Chord Chord::Gm  = Chord(169, "Gm",  {&Note::G_4,  &Note::Bb_4, &Note::D_5});
Chord Chord::Abm = Chord(170, "Abm", {&Note::Ab_4, &Note::B_4,  &Note::E_5});
Chord Chord::Am  = Chord(171, "Am",  {&Note::A_4,  &Note::C_5,  &Note::E_5});
Chord Chord::Bbm = Chord(172, "Bbm", {&Note::Bb_4, &Note::Db_5, &Note::F_5});
Chord Chord::Bm  = Chord(173, "Bm",  {&Note::B_4,  &Note::D_5,  &Note::F_5});

// Dominant 7th Chords
Chord Chord::C7  = Chord(174, "C7",  {&Note::C_4,  &Note::E_4,  &Note::G_4,  &Note::Bb_4});
Chord Chord::Db7 = Chord(175, "Db7", {&Note::Db_4, &Note::F_4,  &Note::Ab_4, &Note::C_5});
Chord Chord::D7  = Chord(176, "D7",  {&Note::D_4,  &Note::F_4,  &Note::A_4,  &Note::C_5});
Chord Chord::Eb7 = Chord(177, "Eb7", {&Note::Eb_4, &Note::G_4,  &Note::Bb_4, &Note::D_5});
Chord Chord::E7  = Chord(178, "E7",  {&Note::E_4,  &Note::G_4,  &Note::B_4,  &Note::D_5});
Chord Chord::F7  = Chord(179, "F7",  {&Note::F_4,  &Note::A_4,  &Note::C_5,  &Note::Eb_5});
Chord Chord::Gb7 = Chord(180, "Gb7", {&Note::Gb_4, &Note::Bb_4, &Note::Db_5, &Note::E_5});
Chord Chord::G7  = Chord(181, "G7",  {&Note::G_4,  &Note::B_4,  &Note::D_5,  &Note::F_5});
Chord Chord::Ab7 = Chord(182, "Ab7", {&Note::Ab_4, &Note::C_5,  &Note::Eb_5, &Note::Gb_5});
Chord Chord::A7  = Chord(183, "A7",  {&Note::A_4,  &Note::C_5,  &Note::E_5,  &Note::G_5});
Chord Chord::Bb7 = Chord(184, "Bb7", {&Note::Bb_4, &Note::D_5,  &Note::F_5,  &Note::Ab_5});
Chord Chord::B7  = Chord(185, "B7",  {&Note::B_4,  &Note::D_5,  &Note::F_5,  &Note::A_5});

// Diminished 7th Chords
Chord Chord::Cdim  = Chord(186, "Cdim",  {&Note::C_4,  &Note::Eb_4, &Note::Gb_4, &Note::A_4});
Chord Chord::Dbdim = Chord(187, "Dbdim", {&Note::Db_4, &Note::E_4,  &Note::G_4,  &Note::Bb_4});
Chord Chord::Ddim  = Chord(188, "Ddim",  {&Note::D_4,  &Note::F_4,  &Note::Ab_4, &Note::C_5});
Chord Chord::Ebdim = Chord(189, "Ebdim", {&Note::Eb_4, &Note::Gb_4, &Note::A_4,  &Note::C_5});
Chord Chord::Edim  = Chord(190, "Edim",  {&Note::E_4,  &Note::G_4,  &Note::Bb_4, &Note::D_5});
Chord Chord::Fdim  = Chord(191, "Fdim",  {&Note::F_4,  &Note::Ab_4, &Note::C_5,  &Note::E_5});
Chord Chord::Gbdim = Chord(192, "Gbdim", {&Note::Gb_4, &Note::A_4,  &Note::C_5,  &Note::Eb_5});
Chord Chord::Gdim  = Chord(193, "Gdim",  {&Note::G_4,  &Note::Bb_4, &Note::Db_5, &Note::E_5});
Chord Chord::Abdim = Chord(194, "Abdim", {&Note::Ab_4, &Note::C_5,  &Note::Eb_5, &Note::G_5});
Chord Chord::Adim  = Chord(195, "Adim",  {&Note::A_4,  &Note::C_5,  &Note::Eb_5, &Note::G_5});
Chord Chord::Bbdim = Chord(196, "Bbdim", {&Note::Bb_4, &Note::Db_5, &Note::E_5,  &Note::G_5});
Chord Chord::Bdim  = Chord(197, "Bdim",  {&Note::B_4,  &Note::D_5,  &Note::F_5,  &Note::A_5});
