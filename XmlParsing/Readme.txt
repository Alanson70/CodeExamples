Xml Parsing module
(Translated by Yandex)
The presented C++ code implements part of the module of the car order management system. 
The task of the module is to import data with orders from various sources and formats.
In the end, all variants of the original data are reduced to a single - in the form of structured arrays (buffers), 
which come to the level of business logic and then to the database.
Parsing XML files was initially based on the DOM algorithm, 
however, in connection with the sharp growth of volumes of files and requirements to expedite the processing,
there was a need to switch to a faster and memory-less algorithm SAX. 
The peculiarity of the replacement was also in the categorical unwillingness to change the module code, 
using Dom features such as random access to xml structure elements.
However, this applies to the submitted code only indirectly.