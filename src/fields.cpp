// Copyright 2021 Chun Shen

#include "fields.h"
#include "cell.h"


Fields::~Fields() {
    e_.clear();
    rhob_.clear();
    piBulk_.clear();
    u_.clear();
    Wmunu_.clear();
}


void Fields::resizeFields(int Nx, int Ny, int Neta) {
    Nx_   = Nx;
    Ny_   = Ny;
    Neta_ = Neta;
    int Npoints = Nx*Ny*Neta;

    e_.resize(Npoints, 0.);
    rhob_.resize(Npoints, 0.);
    piBulk_.resize(Npoints, 0.);

    u_.resize(Nu_);
    u_[0].resize(Npoints, 1.);
    for (int i = 1; i < Nu_; i++) {
        u_[i].resize(Npoints, 0.);
    }

    Wmunu_.resize(NWmunu_);
    for (int i = 0; i < NWmunu_; i++) {
        Wmunu_[i].resize(Npoints, 0.);
    }
}


Cell_small Fields::getCell(int ix, int iy, int ieta) {
    int idx = getFieldIdx(ix, iy, ieta);
    Cell_small cell;
    cell.epsilon = e_[idx];
    cell.rhob = rhob_[idx];
    for (int i = 0; i < Nu_; i++) {
        cell.u[i] = u_[i][idx];
    }
    for (int i = 0; i < NWmunu_; i++) {
        cell.Wmunu[i] = Wmunu_[i][idx];
    }
    cell.pi_b = piBulk_[idx];
    return(cell);
}

