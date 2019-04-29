@echo off

if exist    *.o                    (del /f /q *.o)
if exist    *.a                    (del /f /q *.a)
if exist    *.dll                  (del /f /q *.dll)
if exist    *.exe                  (del /f /q *.exe)
if exist    *.layout               (del /f /q *.layout)
