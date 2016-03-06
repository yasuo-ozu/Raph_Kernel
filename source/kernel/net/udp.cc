/*
 *
 * Copyright (c) 2016 Raphine Project
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

#include "udp.h"
#include "../raph.h"
#include "../mem/physmem.h"
#include "../mem/virtmem.h"
#include "../global.h"

int32_t UDPCtrl::GenerateHeader(uint8_t *buffer, uint32_t length, uint16_t sport, uint16_t dport) {
  UDPHeader * volatile header = reinterpret_cast<UDPHeader*>(buffer);
  header->sport    = htons(sport);
  header->dport    = htons(dport);
  header->len      = htons(sizeof(UDPHeader) + length);
  header->checksum = 0;
  return 0;
}

bool UDPCtrl::FilterPacket(uint8_t *packet, uint16_t sport, uint16_t dport) {
  UDPHeader * volatile header = reinterpret_cast<UDPHeader*>(packet);
  return (ntohs(header->sport) == sport)
      && (ntohs(header->dport) == dport);
}
