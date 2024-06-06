#exemplo de uso de futuros em Python

import concurrent.futures
import time

#funcao que sera executada de forma assincrona
def task(x):
    for i in range(50000000):
        pass
    return x ** 2

if __name__ == '__main__':
    start = time.time()
    #cria um pool de threads OU de processos com no maximo 5 intancias 
    with concurrent.futures.ProcessPoolExecutor(max_workers=5) as executor:
        tarefas = []
        
        #submete a tarefa para execucao assincrona
        for aux in range(10):
            tarefas.append(executor.submit(task, aux))
        
        #...pode fazer alguma computacao...e mais adiante no codigo...    
        
        #recebe os resultados
        for tarefa in tarefas:
            resultado = tarefa.result()
            print(resultado)
    end = time.time()
    print('work took {} seconds'.format(end - start))
