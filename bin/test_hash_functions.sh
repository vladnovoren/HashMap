# $1 - путь к словарю. $2 - путь к папке с *.csv и *.gpi файлами
./test_hash_functions $1 $2
cd $2
gnuplot ASCII_SumHash.gpi
gnuplot ConstantHash.gpi
gnuplot FirstCharHash.gpi
gnuplot FirstCharHashScaled.gpi
gnuplot strlenHash.gpi
gnuplot strlenHashScaled.gpi
gnuplot Crc32Hash.gpi
gnuplot RolHash.gpi