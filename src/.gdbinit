
define showfreemem
  set $n = freemem
  while $n != 0
    print *$n
    set $n = $n->next
  end
end

define showusedmemblock
  set $memblock = $arg0
  print *$memblock
  set $size = $memblock->size
  set $counter = 0
  while $size >= $counter
    print *((char*)$memblock + 8 + $counter)
    set $counter = $counter + 1
  end
end

define showheap
  set $heap = mempool
  set $curr = (struct memblock) $heap
  while $curr < ($heap + 16533) && $curr != 0
    print *$curr
    set $size = $curr->size
    set $counter = 0
    while $size >= $counter
      print *((char*)$memblock + 8 + $counter)
      set $counter = $counter + 1
    end
    set $curr = ((char*)$memblock + 8 + $size)
  end
end