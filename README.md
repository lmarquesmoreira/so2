Trabalhos de SO2 - 2014.1
===

Bom galera, o de MPI, eu o Fred ainda não terminamos ele 100% :/ <br />Então em breve já vamos disponibilizar ((:

Para executar é o de sempre:
<code> gcc forkMatriz.c -o fork -w</code><br/>
Para o de Thread tem que adicionar -lpthread:
<code> gcc threadMatriz.c -o thread -lpthread -w</code><br/>
E para executar é simples também
<code> ./fork 2000 8 </code>


Testando com o time
===

Recomendo que testem os codigos, os nossos, os de vocês e etc. ((: 

<h2>Breve Comparativo</h2>

Exemplo:<br/>
<br/><code>time ./fork 2000 8</code>
<br/><code>time ./thread 2000 8</code>

<table>
  <tr>
    <th> </th>
    <th> 1 </th>
    <th> 2 </th>
    <th> 4 </th>
    <th> 8 </th>
  </tr>
  <tr>
    <td> Fork </td>
    <td> 0m0.280s </td>
    <td> 0m0.360s </td>
    <td> 0m0.800s </td>
    <td> 0m1.144s </td>
  </tr>  
  <tr>
    <td> Threads </td>
    <td> 0 </td>
    <td> 0 </td>
    <td> 0 </td>
    <td> 0 </td>
  </tr>  
</table>
