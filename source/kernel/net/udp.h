/*
 *
 * Copyright (c) 2016 Project Raphine
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Author: Levelfour
 * 
 */

#ifndef __RAPH_KERNEL_NET_UDP_H__
#define __RAPH_KERNEL_NET_UDP_H__

#include <stdint.h>
#include "layer.h"
#include "ip.h"

struct UDPHeader {
  // source port
  uint16_t sport;
  // destination port
  uint16_t dport;
  // length (header + datagram)
  uint16_t len;
  // checksum
  uint16_t checksum;
} __attribute__ ((packed));

class UDPCtrl : public L4Ctrl {
  static const uint32_t kDstPortOffset = 2;

public:
  UDPCtrl() {}
  virtual int32_t GenerateHeader(uint8_t *buffer,
                                 uint32_t length,
                                 uint16_t sport,
                                 uint16_t dport);
  virtual bool FilterPacket(uint8_t *packet,
                            uint16_t sport,
                            uint16_t dport);
};

#endif // __RAPH_KERNEL_NET_UDP_H__
