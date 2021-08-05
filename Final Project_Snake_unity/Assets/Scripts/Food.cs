using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Food : MonoBehaviour
{
    // Define the gird that shows boundry of food position
    // Because ower food boundry has component BoxCollider2D
    // We have to refrence GridArea in unity to food-boundry 
    public BoxCollider2D GridArea;

    public void Start()
    {
        RandomFoodPosition();
    }

    // Select a random position for food object
    private void RandomFoodPosition()
    {
        // BoxCollider has a property of Bounds that gives us size of everything
        Bounds bound = this.GridArea.bounds;

        // Selects a random number in the specified range for x and y 
        float x = Random.Range(bound.min.x, bound.max.x);

        float y = Random.Range(bound.min.y, bound.max.y);

        // Set the food position but round the values to ensure it aligns with the grid
        this.transform.position = new Vector2(Mathf.Round(x), Mathf.Round(y));

    }

    // If other Collider2D collides with food, we should call RandomFoodPosition for a new food object
    private void OnTriggerEnter2D(Collider2D other)
    {
        RandomFoodPosition();
    }

}
