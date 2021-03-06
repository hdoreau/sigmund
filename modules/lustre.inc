#!/bin/bash

########################## TEST HELPERS ##################


############################ TEST FUNCTIONS ############################

### test71c: check that file creation is properly forbidden under .lustre/
SPEED[test71c]=fast
NEEDS_ROOT[test71c]=no
function test71c
{
    file="file.$TEST_USER.$$"

    touch $TEST_DIR/.lustre/$file && error "File creation forbidden under .lustre"

    # cleanup just in case...
    rm -rf $TEST_DIR/.lustre/$file
}

### test71d: check that directory creation is properly forbidden under .lustre/
SPEED[test71d]=fast
NEEDS_ROOT[test71d]=no
function test71d
{
    dir="dir.$TEST_USER.$$"

    mkdir $TEST_DIR/.lustre/$dir && error "Directory creation forbidden under .lustre"

    # cleanup just in case...
    rm -rf $TEST_DIR/.lustre/$dir
}

### test71h: check that hardlink creation is properly forbidden under .lustre/
SPEED[test71h]=fast
NEEDS_ROOT[test71h]=no
function test71h
{
    file="dir.$TEST_USER.$$"

    touch $TEST_DIR/$file
    ln $TEST_DIR/$file $TEST_DIR/.lustre/$file && error "Hardlink creation forbidden under .lustre"

    # cleanup just in case...
    rm -rf $TEST_DIR/$file $TEST_DIR/.lustre/$file
}

### test72: check that attempts to unlink .lustre/ fail
SPEED[test72]=fast
NEEDS_ROOT[test72]=no
function test72
{
    rm -rf $TEST_DIR/.lustre && error "Unlinking .lustre/ is not permitted"
}

### test73: Execute binaries from lustre
SPEED[test73]=fast
NEEDS_ROOT[test73]=no
function test73
{
    BIN=`which ls`
    cp $BIN $TEST_DIR
    chmod go+rw $TEST_DIR/ls
    $DIR/ls / || error "Cannot run binaries from lustre"
    rm -f $DIR/ls
}


# syntax: ONLY=2,3 ./run_test.sh [-j] <test_dir>

######################## DEFINE TEST LIST HERE ####################

function run_lustre
{
  run_test test71c  " LUSTRE: file creation forbidden under .lustre       "
  run_test test71d  " LUSTRE: directory creation forbidden under .lustre  "
  run_test test71h  " LUSTRE: hardlinking forbidden under .lustre         "
  run_test test72   " LUSTRE: unlinking .lustre should fail               "
  run_test test73   " LUSTRE: running binaries from lustre                "
}

