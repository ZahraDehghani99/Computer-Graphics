using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Snake : MonoBehaviour
{

    // Initial movement direction of snake 
    public Vector2 direction = Vector2.right;

    // Store segments of snake
    private List<Transform> segments;

    // For add segments into segment list
    public Transform SegmentPrefab;



    public void Start()
    {
        // Set the fixed time stamp and decrease it in update function to increase the movement speed of snake
        Time.fixedDeltaTime = 0.06f;

        segments = new List<Transform>();
        segments.Add(this.transform); // head of snake

    }


    // Update is called once per frame
    public void Update()
    {
        // Move horizontal --> allow turning up or down
        if (this.direction.x != 0.0f)
        {
            //Control the direction of snake with UpArrow, DownArrow, RightArrow and LeftArrow

            if (Input.GetKey(KeyCode.UpArrow))
            {
                direction = Vector2.up;
            }
            else if (Input.GetKey(KeyCode.DownArrow))
            {
                direction = Vector2.down;
            }
        }

        // Move vertical --> allow turning right or left
        else if (this.direction.y != 0.0f)
        {
            if (Input.GetKey(KeyCode.RightArrow))
            {
                direction = Vector2.right;
            }
            else if (Input.GetKey(KeyCode.LeftArrow))
            {
                direction = Vector2.left;
            }
        }

        // Increase the movement speed of snake dependent to its length

        if (GameManager.Instance.length >= 2 && GameManager.Instance.length <= 4)
        {
            Time.fixedDeltaTime = 0.05f; 
        }
        else if (GameManager.Instance.length >= 5 && GameManager.Instance.length <= 7)
        {
            Time.fixedDeltaTime = 0.04f;
        }
        else if (GameManager.Instance.length >= 8)
        {
            Time.fixedDeltaTime = 0.03f;
        }

    }

    //  Updated for fixed timeframe independent of device fps (equivalent to Time.deltatime)
    public void FixedUpdate()
    {
        // Set each segment's position to be the same as the one it follows. 
        // We must do this in reverse order so the position is set to the previous position, otherwise they will all be stacked on top of each other.
        for (int i = segments.Count-1; i > 0; i--)
            {
            segments[i].position = segments[i - 1].position;
            }


        // Update the position of snake. Round each component of vector to ensure that it stays aligned to the grid.
        transform.position = new Vector3( Mathf.Round(transform.position.x) + direction.x , Mathf.Round(transform.position.y) + direction.y);


    }

    private void GrowSnake()
    {
        // Create clone of segmentprefab
        Transform segment = Instantiate(this.SegmentPrefab);

        // Add new segment at the end of the Snake tail
        segment.position = segments[segments.Count - 1].position;

        segments.Add(segment);
        

    }
    // If other Collider2D(food) collides with snake, the length of snake should become large
    private void OnTriggerEnter2D(Collider2D other)
    {
        // Because if snake collides with its segment --> Game Over
        if (other.tag == "food")
        {
            GrowSnake();
            
            // Increase snake length
            GameManager.Instance.length += 1;
            GameManager.Instance.length_text.text = GameManager.Instance.length.ToString();

        }

        if (other.tag == "obstacle")
        {
            GameManager.Instance.GameOver();

        }
    }
}
