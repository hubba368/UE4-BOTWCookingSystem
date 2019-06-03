# UE4-BOTWCookingSystem
An attempt at replicating the Cooking mechanics from The Legend of Zelda: Breath Of The Wild.

In BOTW, the cooking mechanics essentially work like this:

* Choose ingredients and add them to cooking pot.
* A 'recipe' is chosen from the ingredients, determining the initial name and inventory image.
* The stat related variables such as health and stamina restoration are calculated depending on the ingredients.

The cooking system in BOTW is interesting, mainly because you do not necessarily choose what recipe you want to make (outside of memorising or using a guide). This gives it the illusion that you can make 'anything' with the ingredients you can use, when it actuality it's just a big, hidden recipe list.

I've essentially attempted to remake this mechanic in UE4, with the ability for it to be easily extendable depending on what I want to use it for. It works like this:

* Ingredients are added to a Cooking Pot Actor
* A recipe is chosen, depending on:
  * if the ingredients match up with the requirements of a recipe, stored in a UDataTable.
  * if a recipe is chosen, return the name of the recipe.
 * Calculate the effects of the end product:
  * calculate health restoration (sum of all restore vals) x 2.
  * if the ingredient list has all of the same effect types, e.g. attack boost:
    * calc effect vals e.g. duration, potency.
  * Assemble the final recipe name, depending on if there is a secondary boost applied, and the potency.
  

 
