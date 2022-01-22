#!/bin/bash

diff <(nm $1 2>&1) <(./ft_nm $1 2>&1)