# Library Catalog System

## Overview

This repository contains the implementation of a simple library catalog system where users can search for books or authors, and administrators can perform various operations such as adding, updating, and deleting records.

## Data Storage

The data for authors and books is stored in delimited fields and length indicator records.

## Indexing

The following indexes are implemented:

- Primary index using Author ID (for Authors data file).
- Primary index using ISBN (for Books data file).
- Secondary index using Author ID (for the Books data file).
- Secondary index using Author Name (for the Authors data file).

## Operations

### Add, Update, and Delete Functions

- When adding a record, the system first looks at the AVAIL LIST, then writes the record. If a record is available in the AVAIL LIST, it is written to the record AVAIL LIST points, and appropriate changes are made on the AVAIL LIST.
- If the record to be added already exists, it is not written to the file.
- When deleting a record, the system does not physically delete it but puts a marker (*) on the file and makes appropriate changes on the AVAIL LIST. If the record to be deleted does not exist, a warning message is displayed.
- For the update function, updates are made to non-key fields only, and updates to these fields will not exceed the allocated size. All add and delete operations affect indexes.

### Search Operations

- Search operations use indexes (primary or secondary).
- All indexes are sorted in ascending order.
- Searching in indexes is performed using Binary search.
- Secondary indexes are implemented using the linked list technique.


