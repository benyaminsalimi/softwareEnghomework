from random import randint, random, uniform
## sakhte yek fard
def individual(length, min, max):
    return [ uniform(min,max) for x in xrange(length) ]
## sakhte jamiyat 
def population(count, length, min, max):
    return [ individual(length, min, max) for x in xrange(count) ]
## tabe fit
def fitness(individual, target):
    y1= float(0.26) * (individual[0]**float(2) + individual[1]**float(2))
    y2 = -0.48*individual[0]*individual[1]
    y = y1 + y2
    return abs(y-target) ## chon az jens fasele hast har chi kamtar bashad behtar ast !
## garde dehi baraye payda kardan behtarin dar har jamiyat !
def grade(pop, target):
    graded = [ (fitness(x, target), x) for x in pop]
    graded = [ x[1] for x in sorted(graded)]
    return graded[0]
### jahesh 
def evolve(pop, target, retain=0.1, random_select=0.05, mutate=0.15):
    ## sort kardan jamiyat 
    graded = [ (fitness(x, target), x) for x in pop]
    graded = [ x[1] for x in sorted(graded)]
    retain_length = int(len(graded)*retain)
    parents = graded[:retain_length] ## entkhab behtarin ha 
    
    ## darsadi az jamiyat ke bayad taghir konad ! baraye jolo giri az yeksan shodan jamiyt
    ## for uniform added
    for individual in parents:
        for x in xrange(int(retain_length*mutate)):
            pos_to_mutate = randint(0, len(individual)-1)
            individual[pos_to_mutate] = uniform(-5,5) ### max and min can be better ! with pass to function
    ### barye in ke jamiyat armani nashavad!
    ### be soorate tasadofi entkhab mikonad ke ki baghu bemand !
    for individual in graded[retain_length:]:
        if random_select > random():
            parents.append(individual)
    
    ### tolid mesl kardan jamiyate avliyeh !
    parents_length = len(parents)
    desired_length = len(pop) - parents_length
    children = []
    while len(children) < desired_length:
        male = randint(0, parents_length-1)
        female = randint(0, parents_length-1)
        if male != female:
            male = parents[male]
            female = parents[female]
            half = len(male) / 2
            child = male[:half] + female[half:]
            children.append(child)
    parents.extend(children)
    return parents




print "##################### Start #####################"
target = 0 ##hadaf 
p_count = 100 #jamiyate avaliyeh
i_length = 2 # har fard
i_min = -10 #min
i_max = 10 # max
p = population(p_count, i_length, i_min, i_max) # saskhte ahade mardom iran
fitness_history = [fitness(grade(p, target), target),] #best fitness of population
print "best gen :"
print grade(p, target)
print "fitness : "
print fitness(grade(p, target), target)

while True:
    p = evolve(p, target) 
    print "################################"
    print "best gen :" 
    print grade(p, target)
    print "fitness : "
    print fitness(grade(p, target), target)
    fitness_history.append(fitness(grade(p, target), target))
    if fitness(grade(p, target),target) < 0.00001:
        break
print "##################### End #####################"
"""
print "##################### fitness history report #####################"
for his in fitness_history:
   print his
"""
"""
TODO : evolve function with wight of each ValueError
TODO : mutate can be better !
"""