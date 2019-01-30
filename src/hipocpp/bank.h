/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   bank.h
 * Author: gavalian
 *
 * Created on April 12, 2017, 10:14 AM
 */

#ifndef HIPO_BANK_H
#define HIPO_BANK_H
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include "node.h"
#include "reader.h"

namespace hipo {

class bank {
 private:
  std::vector<generic_node*> bankNodes;

 public:
  bank();
  bank(const char* bankName, hipo::reader& r);

  ~bank();

  void show();
  int getSize();
  int getInt(int item, int order);
  float getFloat(int item, int order);

  template <class T>
  T getValue(int item, int order);
};

}  // namespace hipo

#endif /* EVENT_H */
