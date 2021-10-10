#!/usr/bin/env python
# coding: utf-8

# In[1]:


import random


# In[2]:


def union_set(subsets):
    union = []
    for subset in subsets:
        for elem in subset:
            if elem in union:
                continue
            union.append(elem)
    return union


# In[3]:


def generate_input(n):
    m = random.randint(1, 500)
    subsets = []
    weights = []
    
    for _ in range(m):
        length = random.randint(1, n)
        subset = []
        
        while len(subset) < length:
            num = random.randint(1, n)
            if num not in subset:
                subset.append(num)
                
        subsets.append(subset)
        weights.append(random.randint(1, 1000))
        
    #Check if subsets follow rule of the union being the universal set.
    union = union_set(subsets)
    universal_set = [*range(1, n+1)]
#     print(universal_set)
#     union.sort()
#     print(union)
    
    #If they don't then find missing elements and add them to a random number of subsets with random selection.
    if union != universal_set:
        for elem in universal_set:
            if elem not in union:
#                 print(elem)
                for _ in range(random.randint(1, m)):
                    index = random.randint(0, m-1)
                    if elem not in subsets[index]:
                        subsets[index].append(elem)
    
    return subsets, weights


# In[4]:


n = 1000
subsets, weights = generate_input(n)
m = len(subsets)


# In[5]:


#Print to a file
f = open('input_rand.txt', 'w')
f.write(str(n))

f.write("\n")
f.write(str(m))

for i in range(m):
    f.write("\n")
    
    line = ""
    for elem in subsets[i]:
        line += (str(elem) + " ")
    f.write(line.strip())
    
    f.write("\n")
    f.write(str(weights[i]))
    
f.close()

