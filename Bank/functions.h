#pragma once

void addNewClient();
void decryptClientToFile(const char *filename, char key[20]);
void searchClient(const char *filename, char key[20], char _pers_acc[20]);
void deleteClient(const char *filename, char key[20], char _pers_acc[20]);