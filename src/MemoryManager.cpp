/*
 * Created by He, Hao at 2019-3-11
 */

 #include "MemoryManager.h"
 #include "Debug.h"
 
 #include <cstdio>
 #include <string>
 
 MemoryManager::MemoryManager() {
   this->cache = nullptr;
   this->memory = new uint8_t[UINT32_MAX];
   memset(this->memory, 0, UINT32_MAX);
 }
 
 MemoryManager::~MemoryManager() {
   delete[] this->memory;
 }
 
 bool MemoryManager::addPage(uint32_t addr) {
   dbgprintf("addPage() called but paging is disabled.\n");
   return true;
 }
 
 bool MemoryManager::isPageExist(uint32_t addr) {
   dbgprintf("isPageExist() called but paging is disabled.\n");
   return true;
 }
 
 bool MemoryManager::copyFrom(const void *src, uint32_t dest, uint32_t len) {
   for (uint32_t i = 0; i < len; ++i) {
     if (!this->isAddrExist(dest + i)) {
       dbgprintf("Data copy to invalid addr 0x%x!\n", dest + i);
       return false;
     }
     this->setByte(dest + i, ((uint8_t *)src)[i]);
   }
   return true;
 }
 
 bool MemoryManager::setByte(uint32_t addr, uint8_t val, uint32_t *cycles) {
   if (!this->isAddrExist(addr)) {
     dbgprintf("Byte write to invalid addr 0x%x!\n", addr);
     return false;
   }
   if (this->cache != nullptr) {
     this->cache->setByte(addr, val, cycles);
     return true;
   }
 
   this->memory[addr] = val;
   return true;
 }
 
 bool MemoryManager::setByteNoCache(uint32_t addr, uint8_t val) {
   if (!this->isAddrExist(addr)) {
     dbgprintf("Byte write to invalid addr 0x%x!\n", addr);
     return false;
   }
 
   this->memory[addr] = val;
   return true;
 }
 
 uint8_t MemoryManager::getByte(uint32_t addr, uint32_t *cycles) {
   if (!this->isAddrExist(addr)) {
     dbgprintf("Byte read to invalid addr 0x%x!\n", addr);
     return false;
   }
   if (this->cache != nullptr) {
     return this->cache->getByte(addr, cycles);
   }
   return this->memory[addr];
 }
 
 uint8_t MemoryManager::getByteNoCache(uint32_t addr) {
   if (!this->isAddrExist(addr)) {
     dbgprintf("Byte read to invalid addr 0x%x!\n", addr);
     return false;
   }
   return this->memory[addr];
 }
 
 bool MemoryManager::setShort(uint32_t addr, uint16_t val, uint32_t *cycles) {
   if (!this->isAddrExist(addr)) {
     dbgprintf("Short write to invalid addr 0x%x!\n", addr);
     return false;
   }
   this->setByte(addr, val & 0xFF, cycles);
   this->setByte(addr + 1, (val >> 8) & 0xFF);
   return true;
 }
 
 uint16_t MemoryManager::getShort(uint32_t addr, uint32_t *cycles) {
   uint32_t b1 = this->getByte(addr, cycles);
   uint32_t b2 = this->getByte(addr + 1);
   return b1 + (b2 << 8);
 }
 
 bool MemoryManager::setInt(uint32_t addr, uint32_t val, uint32_t *cycles) {
   if (!this->isAddrExist(addr)) {
     dbgprintf("Int write to invalid addr 0x%x!\n", addr);
     return false;
   }
   this->setByte(addr, val & 0xFF, cycles);
   this->setByte(addr + 1, (val >> 8) & 0xFF);
   this->setByte(addr + 2, (val >> 16) & 0xFF);
   this->setByte(addr + 3, (val >> 24) & 0xFF);
   return true;
 }
 
 uint32_t MemoryManager::getInt(uint32_t addr, uint32_t *cycles) {
   uint32_t b1 = this->getByte(addr, cycles);
   uint32_t b2 = this->getByte(addr + 1);
   uint32_t b3 = this->getByte(addr + 2);
   uint32_t b4 = this->getByte(addr + 3);
   return b1 + (b2 << 8) + (b3 << 16) + (b4 << 24);
 }
 
 bool MemoryManager::setLong(uint32_t addr, uint64_t val, uint32_t *cycles) {
   if (!this->isAddrExist(addr)) {
     dbgprintf("Long write to invalid addr 0x%x!\n", addr);
     return false;
   }
   this->setByte(addr, val & 0xFF, cycles);
   this->setByte(addr + 1, (val >> 8) & 0xFF);
   this->setByte(addr + 2, (val >> 16) & 0xFF);
   this->setByte(addr + 3, (val >> 24) & 0xFF);
   this->setByte(addr + 4, (val >> 32) & 0xFF);
   this->setByte(addr + 5, (val >> 40) & 0xFF);
   this->setByte(addr + 6, (val >> 48) & 0xFF);
   this->setByte(addr + 7, (val >> 56) & 0xFF);
   return true;
 }
 
 uint64_t MemoryManager::getLong(uint32_t addr, uint32_t *cycles) {
   uint64_t b1 = this->getByte(addr, cycles);
   uint64_t b2 = this->getByte(addr + 1);
   uint64_t b3 = this->getByte(addr + 2);
   uint64_t b4 = this->getByte(addr + 3);
   uint64_t b5 = this->getByte(addr + 4);
   uint64_t b6 = this->getByte(addr + 5);
   uint64_t b7 = this->getByte(addr + 6);
   uint64_t b8 = this->getByte(addr + 7);
   return b1 + (b2 << 8) + (b3 << 16) + (b4 << 24) + (b5 << 32) + (b6 << 40) +
          (b7 << 48) + (b8 << 56);
 }
 
 void MemoryManager::printInfo() {
   printf("Memory Info: \n");
   printf("Single large page covering the entire address space.\n");
 }
 
 void MemoryManager::printStatistics() {
   printf("---------- CACHE STATISTICS ----------\n");
   this->cache->printStatistics();
 }
 
 std::string MemoryManager::dumpMemory() {
   char buf[65536];
   std::string dump;
 
   dump += "Memory Dump: \n";
   for (uint32_t addr = 0; addr < UINT32_MAX; addr += 4096) {
     sprintf(buf, "0x%x-0x%x\n", addr, addr + 4096);
     dump += buf;
     for (uint32_t offset = 0; offset < 4096; ++offset) {
       sprintf(buf, "  0x%x: 0x%x\n", addr + offset, this->memory[addr + offset]);
       dump += buf;
     }
   }
   return dump;
 }
 
 uint32_t MemoryManager::getFirstEntryId(uint32_t addr) {
   return 0;
 }
 
 uint32_t MemoryManager::getSecondEntryId(uint32_t addr) {
   return 0;
 }
 
 uint32_t MemoryManager::getPageOffset(uint32_t addr) {
   return addr;
 }
 
 bool MemoryManager::isAddrExist(uint32_t addr) {
   return addr < UINT32_MAX;
 }
 
 void MemoryManager::setCache(Cache *cache) {
   this->cache = cache;
 }
 